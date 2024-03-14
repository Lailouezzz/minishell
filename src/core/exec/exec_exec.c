/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amassias <amassias@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 15:34:01 by amassias          #+#    #+#             */
/*   Updated: 2024/03/14 15:01:19 by amassias         ###   ########.fr       */
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
				t_heredocs_fds *heredocs_fds,
				t_redirect_list *list
				);

static bool	_open_heredocs_pipeline(
				t_heredocs_fds *heredocs_fds,
				t_pipeline *pipeline
				);

static bool	_open_heredocs(
				t_heredocs_fds *heredocs_fds,
				const t_command_line *comamnd_line
				);

static bool	_open_heredocs_and_or(
				t_heredocs_fds *heredocs_fds,
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
	if (_open_heredocs(&ctx->env_ctx->heredocs, cl))
		return (env_ctx_heredocs_cleanup(ctx->env_ctx), MS_FATAL);
	and_or_executor(ctx, cl->and_or, &error);
	return (env_ctx_heredocs_cleanup(ctx->env_ctx), error);
}

/* ************************************************************************** */
/*                                                                            */
/* Helper implementation                                                      */
/*                                                                            */
/* ************************************************************************** */

static bool	_process(
				t_heredocs_fds *hd,
				t_redirect_list *list
				)
{
	size_t	i;

	i = 0;
	while (list && i < list->used)
	{
		if (list->io_infos[i++].io_type != IO_HEREDOC)
			continue ;
		hd->fds[hd->_index] = create_heredoc(list->io_infos[i - 1].file);
		if (hd->fds[hd->_index] < 0)
			return (true);
		list->io_infos[i - 1].fd = hd->fds[hd->_index++];
	}
	return (0);
}

static bool	_open_heredocs_pipeline(
				t_heredocs_fds *hd,
				t_pipeline *pipeline
				)
{
	t_command	*command_ptr;
	void		*command;

	command_ptr = &pipeline->commands[0];
	while (command_ptr < pipeline->commands + pipeline->used)
	{
		command = command_ptr->command;
		if ((command_ptr->type == COMMAND_SUBSHELL
				&& (_open_heredocs_and_or(hd, ((t_subshell *)command)->and_or)
					|| _process(hd, ((t_subshell *)command)->redirect_list)))
			|| (command_ptr->type != COMMAND_SUBSHELL
				&& _process(hd, ((t_simple_command *)command)->redirect_list)))
			return (true);
		++command_ptr;
	}
	return (false);
}

static bool	_open_heredocs(
				t_heredocs_fds *heredocs_fds,
				const t_command_line *command_line
				)
{
	heredocs_fds->count = u_count_heredocs(command_line);
	heredocs_fds->fds = (int *)malloc(heredocs_fds->count * sizeof(int));
	return (heredocs_fds->fds == NULL
		|| _open_heredocs_and_or(heredocs_fds, command_line->and_or));
}

static bool	_open_heredocs_and_or(
				t_heredocs_fds *heredocs_fds,
				t_and_or *and_or
				)
{
	if (and_or == NULL)
		return (false);
	if (_open_heredocs_and_or(heredocs_fds, and_or->left))
		return (true);
	return (_open_heredocs_pipeline(heredocs_fds, and_or->right_pipeline));
}
