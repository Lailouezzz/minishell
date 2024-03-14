/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _utils2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amassias <amassias@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 16:58:00 by amassias          #+#    #+#             */
/*   Updated: 2024/03/14 14:58:40 by amassias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file _utils.c
 * @author Antoine Massias (amassias@student.42lehavre.fr)
 * @date 2024-03-11
 * @copyright Copyright (c) 2024
 */

/* ************************************************************************** */
/*                                                                            */
/* Includes                                                                   */
/*                                                                            */
/* ************************************************************************** */

#include "core/_exec.h"

#include <libft.h>
#include <stdlib.h>

/* ************************************************************************** */
/*                                                                            */
/* Helper protoypes                                                           */
/*                                                                            */
/* ************************************************************************** */

static void	_count_heredocs(
				size_t *cnt,
				t_and_or *and_or
				);

/* ************************************************************************** */
/*                                                                            */
/* Header implementation                                                      */
/*                                                                            */
/* ************************************************************************** */

size_t	u_count_heredocs(
			const t_command_line *command_line
			)
{
	size_t	count;

	count = 0;
	_count_heredocs(&count, command_line->and_or);
	return (count);
}

/* ************************************************************************** */
/*                                                                            */
/* Helper implementation                                                      */
/*                                                                            */
/* ************************************************************************** */

static void	_count_heredocs(
				size_t *cnt,
				t_and_or *and_or
				)
{
	t_pipeline		*pl;
	t_command		*cmd;
	t_redirect_list	*rl;
	t_io_info		*io;

	if (and_or == NULL)
		return ;
	pl = and_or->right_pipeline;
	cmd = pl->commands - 1;
	while (++cmd < pl->commands + pl->used)
	{
		if (cmd->type == COMMAND_SUBSHELL)
			_count_heredocs(cnt, ((t_subshell *)cmd->command)->and_or);
		if (cmd->type == COMMAND_SUBSHELL)
			rl = ((t_subshell *)cmd->command)->redirect_list;
		else
			rl = ((t_simple_command *)cmd->command)->redirect_list;
		if (rl == NULL)
			continue ;
		io = rl->io_infos;
		while (io < rl->io_infos + rl->used)
			if ((io++)->io_type == IO_HEREDOC)
				++*cnt;
	}
	_count_heredocs(cnt, and_or->left);
}
