/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _utils1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amassias <amassias@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 16:58:00 by amassias          #+#    #+#             */
/*   Updated: 2024/03/14 14:53:49 by amassias         ###   ########.fr       */
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
/* Header implementation                                                      */
/*                                                                            */
/* ************************************************************************** */

const char	*u_get_end(
				const char *str
				)
{
	const char	*end;

	end = ft_strchr(str, '\n');
	if (end == NULL)
		end = ft_strchr(str, '\0');
	return (end);
}

void	u_free_list(
				void ***list_ptr
				)
{
	void	**itr;

	if (*list_ptr == NULL)
		return ;
	itr = *list_ptr;
	while (*itr)
		free(*itr++);
	free(*list_ptr);
	*list_ptr = NULL;
}

noreturn void	u_quit(
					t_exec_ctx *ctx,
					t_ms_error error
					)
{
	t_ms_status	status;

	status = ctx->env_ctx->current_code;
	if (error == MS_FATAL)
	{
		dprintf(STDERR_FILENO, MS "internal error\n");
		status = MS_STATUS_FAILURE;
	}
	else if (error == MS_BAD_ALLOC)
	{
		dprintf(STDERR_FILENO, MS "out of resources\n");
		status = MS_STATUS_FAILURE;
	}
	else if (error == MS_COMMAND_NOT_FOUND)
		status = MS_STATUS_COMMAND_NOT_FOUND;
	else if (error == MS_PERM_DENIED)
		status = MS_STATUS_PERM_DENIED;
	exec_cleanup_exit(ctx, status);
}

void	u_conditional_close(
			bool close_pipe,
			int pipe_fd[2],
			int out_fd
			)
{
	if (close_pipe)
		(close(pipe_fd[0]), close(pipe_fd[1]));
	close(out_fd);
}
