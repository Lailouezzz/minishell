/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _exec.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amassias <amassias@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 16:37:45 by amassias          #+#    #+#             */
/*   Updated: 2024/03/14 14:52:33 by amassias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file _exec.h
 * @author Antoine Massias (amassias@student.42lehavre.fr)
 * @date 2024-03-11
 * @copyright Copyright (c) 2024
 */

#ifndef _EXEC_H
# define _EXEC_H

/* ************************************************************************** */
/*                                                                            */
/* Includes                                                                   */
/*                                                                            */
/* ************************************************************************** */

# include "core/exec.h"

# include <libft.h>
# include <stdbool.h>
# include <stdio.h>
# include <unistd.h>

/* ************************************************************************** */
/*                                                                            */
/* Defines                                                                    */
/*                                                                            */
/* ************************************************************************** */

# define MS "minishell: "

# define ERR_CMD_NOT_FOUND "%s: command not found"

/* ************************************************************************** */
/*                                                                            */
/* Header protoypes                                                           */
/*                                                                            */
/* ************************************************************************** */

bool			handle_redirect_list(
					const t_redirect_list *list
					);

t_ms_error		run_command(
					t_exec_ctx *ctx,
					const char *program_name,
					const char **args
					);

t_ms_error		launch_command(
					t_env_ctx *ctx,
					const char *program_name,
					const char *path,
					const char **args
					);

t_ms_error		execute_simple_command(
					t_exec_ctx *ctx,
					t_simple_command *command
					);

t_ms_error		execute_subshell(
					t_exec_ctx *ctx,
					t_subshell *command
					);

bool			execute_pipeline(
					t_exec_ctx *ctx,
					const t_pipeline *pipeline,
					t_ms_error *error
					);

bool			and_or_executor(
					t_exec_ctx *ctx,
					const t_and_or *and_or,
					t_ms_error *error
					);

int				create_heredoc(
					const char *delim
					);

size_t			u_count_heredocs(
					const t_command_line *command_line
					);

const char		*u_get_end(
					const char *str
					);

void			u_free_list(
					void ***list_ptr
					);

noreturn void	u_quit(
					t_exec_ctx *ctx,
					t_ms_error error
					);

void			u_conditional_close(
					bool close_pipe,
					int pipe_fd[2],
					int out_fd
					);

#endif
