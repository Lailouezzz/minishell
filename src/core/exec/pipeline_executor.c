/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_executor.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amassias <amassias@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 17:55:47 by amassias          #+#    #+#             */
/*   Updated: 2024/03/11 18:23:35 by amassias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file pipeline_executor.c
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
#include "core/builtins.h"

#include <sys/signal.h>
#include <sys/wait.h>
#include <unistd.h>

/* ************************************************************************** */
/*                                                                            */
/* Helper protoypes                                                           */
/*                                                                            */
/* ************************************************************************** */

static bool				_test_for_lone_builtin(
							t_exec_ctx *ctx,
							t_simple_command *command,
							t_ms_error *error
							);

static t_ms_error		_parent(
							t_exec_ctx *ctx,
							const t_pipeline *pipeline,
							pid_t pid,
							int pipe_fd[2]
							);

static noreturn void	_child(
							size_t index,
							int fds[3],
							t_command *commands,
							t_exec_ctx *ctx
							);

static t_ms_error		_exec_pipeline_rest(
							t_exec_ctx *ctx,
							t_command *commands,
							size_t index,
							int out_fd
							);

/* ************************************************************************** */
/*                                                                            */
/* Header implementation                                                      */
/*                                                                            */
/* ************************************************************************** */

bool	execute_pipeline(
				t_exec_ctx *ctx,
				const t_pipeline *pipeline,
				t_ms_error *error
				)
{
	pid_t		pid;
	int			pipe_fd[2];

	if (pipeline->used > 1)
	{
		if (pipe(pipe_fd) == -1)
			return (MS_FATAL);
	}
	else if (pipeline->commands[0].type == COMMAND_SIMPLE_COMMAND)
	{
		if (_test_for_lone_builtin(ctx, pipeline->commands[0].command, error))
			return (*error != MS_OK);
	}
	pid = fork();
	if (pid == -1)
	{
		if (pipeline->used > 1)
			(close(pipe_fd[0]), close(pipe_fd[1]));
		return (MS_FATAL);
	}
	if (pid == 0)
		_child(pipeline->used - 1, (int [3]){pipe_fd[0], pipe_fd[1], -1},
			pipeline->commands, ctx);
	*error = _parent(ctx, pipeline, pid, pipe_fd);
	return (*error != MS_OK);
}

/* ************************************************************************** */
/*                                                                            */
/* Helper implementation                                                      */
/*                                                                            */
/* ************************************************************************** */

static bool	_test_for_lone_builtin(
				t_exec_ctx *ctx,
				t_simple_command *command,
				t_ms_error *error
				)
{
	size_t	i;
	int		in;
	int		out;

	i = (size_t)-1;
	while (++i < BUILTIN_COUNT)
	{
		if (ft_strcmp(command->pn, g_builtins[i].name) != 0)
			continue ;
		in = dup(STDIN_FILENO);
		out = dup(STDOUT_FILENO);
		if (in == -1 || out == -1)
			return (close(in), close(out), *error = MS_FATAL, true);
		if (handle_redirect_list(command->redirect_list))
		{
			if (dup2(in, STDIN_FILENO) < 0 || dup2(out, STDOUT_FILENO) < 0)
				return (*error = MS_FATAL, true);
			return (close(in), close(out), env_set_code(ctx->env_ctx, 1), true);
		}
		g_builtins[i].fun(ctx, command->args->args, ctx->env_ctx->env.env_vars);
		if (dup2(in, STDIN_FILENO) < 0 || dup2(out, STDOUT_FILENO) < 0)
			*error = MS_FATAL;
		return (close(in), close(out), true);
	}
	return (false);
}

static t_ms_error	_parent(
						t_exec_ctx *ctx,
						const t_pipeline *pipeline,
						pid_t pid,
						int pipe_fd[2]
						)
{
	t_ms_error	error;
	int			stat;

	error = MS_OK;
	if (pipeline->used > 1)
	{
		close(pipe_fd[0]);
		error = _exec_pipeline_rest(ctx, pipeline->commands, pipeline->used - 1,
				pipe_fd[1]);
	}
	waitpid(pid, &stat, 0);
	env_set_code(ctx->env_ctx, WEXITSTATUS(stat));
	if (WIFSIGNALED(stat))
		env_set_code(ctx->env_ctx, 128 + WTERMSIG(stat));
	return (error);
}

static noreturn void	_child(
							size_t index,
							int fds[3],
							t_command *commands,
							t_exec_ctx *ctx
							)
{
	(signal(SIGINT, SIG_DFL), signal(SIGQUIT, SIG_DFL));
	if (index > 0)
		(dup2(fds[0], STDIN_FILENO), close(fds[0]), close(fds[1]));
	if (fds[2] >= 0)
		(dup2(fds[2], STDOUT_FILENO), close(fds[2]));
	if (commands[index].type == COMMAND_SUBSHELL)
		u_quit(ctx, execute_subshell(ctx, commands[index].command));
	u_quit(ctx, execute_simple_command(ctx, commands[index].command));
}

static t_ms_error	_exec_pipeline_rest(
						t_exec_ctx *ctx,
						t_command *commands,
						size_t index,
						int out_fd
						)
{
	pid_t		pid;
	int			status;
	int			pipe_fd[2];

	if (index-- == 0)
		return (close(out_fd), MS_OK);
	if (index > 0 && pipe(pipe_fd) == -1)
		return (close(out_fd), MS_FATAL);
	if (g_signo == SIGINT)
		return (u_conditional_close(index > 0, pipe_fd, out_fd), MS_OK);
	pid = fork();
	if (pid == -1)
		return (u_conditional_close(index > 0, pipe_fd, out_fd), MS_FATAL);
	if (pid == 0)
		_child(index, (int [3]){pipe_fd[0], pipe_fd[1], out_fd}, commands, ctx);
	close(out_fd);
	if (index > 0)
	{
		close(pipe_fd[0]);
		_exec_pipeline_rest(ctx, commands, index, pipe_fd[1]);
	}
	waitpid(pid, &status, 0);
	return (MS_OK);
}
