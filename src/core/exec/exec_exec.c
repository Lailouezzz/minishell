/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amassias <amassias@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 15:34:01 by amassias          #+#    #+#             */
/*   Updated: 2024/03/12 19:58:46 by amassias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file exec_exec.c
 * @author Antoine Massias (amassias@student.42lehavre.fr)
 * @date 2024-02-08
 * @copyright Copyright (c) 2024
 */

/* ************************************************************************** */
/*                                                                            */
/* Includes                                                                   */
/*                                                                            */
/* ************************************************************************** */

#include "core/_exec.h"

/* ************************************************************************** */
/*                                                                            */
/* Helper protoypes                                                           */
/*                                                                            */
/* ************************************************************************** */

static bool	_process(
				t_redirect_list *list
				);

static bool	_open_heredocs_pipeline(
				t_pipeline *pipeline
				);

static bool	_open_heredocs_and_or(
				t_and_or *and_or
				);

static void	_cleanup(
				t_and_or *and_or
				);

/* ************************************************************************** */
/*                                                                            */
/* Header implementation                                                      */
/*                                                                            */
/* ************************************************************************** */

t_ms_error	exec_exec(
				t_exec_ctx *ctx,
				const t_command_line *cl
				)
{
	t_ms_error	error;

	error = MS_OK;
	if (_open_heredocs_and_or(cl->and_or))
		return (_cleanup(cl->and_or), MS_FATAL);
	and_or_executor(ctx, cl->and_or, &error);
	return (_cleanup(cl->and_or), error);
}

/* ************************************************************************** */
/*                                                                            */
/* Helper implementation                                                      */
/*                                                                            */
/* ************************************************************************** */

static bool	_process(
				t_redirect_list *list
				)
{
	size_t	i;

	i = 0;
	while (list && i < list->used)
	{
		if (list->io_infos[i].io_type == IO_HEREDOC)
		{
			list->io_infos[i].fd = create_heredoc(list->io_infos[i].file);
			if (list->io_infos[i].fd < 0)
				return (true);
		}
		++i;
	}
	return (0);
}

static bool	_open_heredocs_pipeline(
				t_pipeline *pipeline
				)
{
	t_command	*command_ptr;
	void		*command;
	bool		x;

	command_ptr = &pipeline->commands[0];
	while (command_ptr < pipeline->commands + pipeline->used)
	{
		command = command_ptr->command;
		if (command_ptr->type == COMMAND_SIMPLE_COMMAND)
			x = _process(((t_simple_command *)command)->redirect_list);
		else
			x = _process(((t_subshell *)command)->redirect_list)
				|| _open_heredocs_and_or(((t_subshell *)command)->and_or);
		if (x)
			return (true);
		++command_ptr;
	}
	return (false);
}

static bool	_open_heredocs_and_or(
				t_and_or *and_or
				)
{
	if (and_or == NULL)
		return (false);
	if (_open_heredocs_and_or(and_or->left))
		return (true);
	return (_open_heredocs_pipeline(and_or->right_pipeline));
}

static void	_cleanup(
				t_and_or *and_or
				)
{
	t_pipeline		*pl;
	t_command		*cmd_ptr;
	t_redirect_list	*lst;
	t_io_info		*io;

	while (and_or)
	{
		((void)0, pl = and_or->right_pipeline, cmd_ptr = pl->commands);
		while (cmd_ptr++ < pl->commands + pl->used)
		{
			if (cmd_ptr[-1].type == COMMAND_SIMPLE_COMMAND)
				lst = ((t_simple_command *)cmd_ptr[-1].command)->redirect_list;
			else
				(_cleanup(((t_subshell *)cmd_ptr[-1].command)->and_or),
					lst = ((t_subshell *)cmd_ptr[-1].command)->redirect_list);
			if (lst)
			{
				io = lst->io_infos;
				while (io < lst->io_infos + lst->used)
					if ((io++)->fd >= 0)
						close(io[-1].fd);
			}
		}
		and_or = and_or->left;
	}
}
