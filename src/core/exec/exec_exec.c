/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amassias <amassias@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 15:34:01 by amassias          #+#    #+#             */
/*   Updated: 2024/02/12 17:07:32 by amassias         ###   ########.fr       */
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

#include "core/exec.h"

#include <fcntl.h>
#include <libft.h>
#include <stdbool.h>
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

/* ************************************************************************** */
/*                                                                            */
/* Defines                                                                    */
/*                                                                            */
/* ************************************************************************** */

#define O_IN 0
#define O_OT 577
#define O_AP 1601

/* ************************************************************************** */
/*                                                                            */
/* Helper protoypes                                                           */
/*                                                                            */
/* ************************************************************************** */

bool	_exec_exec(
			t_exec_ctx *ctx,
			const t_and_or *and_or,
			t_ms_error *error
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
	_exec_exec(ctx, cl->and_or, &error);
	return (error);
}

/* ************************************************************************** */
/*                                                                            */
/* Helper implementation                                                      */
/*                                                                            */
/* ************************************************************************** */

const char	*_get_end(
				const char *str
				)
{
	const char	*end;

	end = ft_strchr(str, '\n');
	if (end == NULL)
		end = ft_strchr(str, '\0');
	return (end);
}

int	_create_heredoc(
		const char *delim
		)
{
	FILE	*f;
	char	*line;
	char	*end;
	size_t	delim_length;

	f = tmpfile();
	if (f == NULL)
		return (-1);
	delim_length = ft_strlen(delim);
	line = get_next_line(STDIN_FILENO);
	while (line)
	{
		end = (char *)_get_end(line);
		if (ft_strncmp(delim, line, delim_length) == 0
			&& line + delim_length == end)
			break ;
		end = line;
		while (end)
			(void)(write(f->_fileno, end++, 1) == 0);
		free(line);
		line = get_next_line(STDIN_FILENO);
	}
	free(line);
	lseek(f->_fileno, 0, SEEK_SET);
	return (f->_fileno);
}

void	_handle_redirect_list(
			const t_redirect_list *list
			)
{
	size_t		i;
	int			fd;
	t_io_info	*info;

	if (list == NULL)
		return ;
	info = list->io_infos;
	i = 0;
	while (i < list->used)
	{
		if (info->io_type == IO_IN)
			fd = open(info->file, O_IN);
		else if (info->io_type == IO_OUT)
			fd = open(info->file, O_OT, 0666);
		else if (info->io_type == IO_APPEND)
			fd = open(info->file, O_AP, 0666);
		else // if (info->io_type == IO_HEREDOC)
			fd = _create_heredoc(info->file);
		if (fd == -1)
			exit(-1); // TODO: Handle case where `fd == -1`
		if (info->io_type == IO_IN || info->io_type == IO_HEREDOC)
			dup2(fd, STDIN_FILENO);
		else
			dup2(fd, STDOUT_FILENO);
		close(fd);
		++i;
	}
}

char	*_as_full_path(
			const char *file,
			const char *path
			)
{
	size_t	file_name_len;
	size_t	path_len;
	char	*full_path;

	file_name_len = ft_strlen(file);
	path_len = ft_strlen(path);
	full_path = (char *)malloc(file_name_len + path_len + 1 + 1);
	if (full_path == NULL)
		return (NULL);
	ft_memcpy(full_path, path, path_len);
	ft_memcpy(full_path + path_len + 1, file, file_name_len);
	full_path[path_len] = '/';
	full_path[path_len + 1 + file_name_len] = '\0';
	return (full_path);
}

char	**_get_paths(
			t_env *env
			)
{
	t_env_var	*var;

	var = env->env_vars;
	while (*var)
	{
		if (ft_strncmp(*var, "PATH=", 5) == 0)
			return (ft_split((*var) + 5, ':'));
		++var;
	}
	return (ft_split("", ':'));
}

char	*_get_pwd(
			t_env *env
			)
{
	// t_env_var	*var;

	// var = env->env_vars;
	// while (*var)
	// {
	// 	if (ft_strncmp(*var, "PWD=", 4) == 0)
	// 		return (*var + 4);
	// 	++var;
	// }
	(void) env;
	return ("/home/amassias/Documents/minishell");
}

t_ms_error	_run_command(
				const char *program_name,
				const char **args,
				t_env *env
				)
{
	static char	*paths[] = { "/usr/bin", NULL };
	char		**itr;
	char		*path;

	// paths = _get_paths(ctx->env_ctx->env);
	path = _as_full_path(program_name, _get_pwd(env));
	if (access(path, F_OK) == 0)
	{
		if (access(path, X_OK) != 0)
			return (MS_PERM_DENIED);
		execve(path, (char **)args, (char **)env->env_vars);
		return (MS_FATAL);
	}
	itr = paths;
	while (*itr)
	{
		path = _as_full_path(program_name, *itr);
		if (access(path, F_OK) == 0)
		{
			if (access(path, X_OK) != 0)
				return (MS_PERM_DENIED);
			execve(path, (char **)args, (char **)env->env_vars);
			return (MS_FATAL);
		}
		free(path);
		++itr;
	}
	// free paths
	return (MS_COMMAND_NOT_FOUND);
}

t_ms_error	__exec_pipeline(
				t_exec_ctx *ctx,
				t_command *commands,
				size_t index,
				int out_fd
			)
{
	pid_t		pid;
	t_ms_error	error;
	int			stat;
	int			pipe_fd[2];

	if (index == 0)
		return (MS_OK);
	if (index > 1)
		pipe(pipe_fd);
	pid = fork();
	if (pid == -1)
		return (MS_FATAL);
	if (pid != 0)
	{
		close(out_fd);
		if (index > 1)
		{
			close(pipe_fd[0]);
			__exec_pipeline(ctx, commands, index - 1, pipe_fd[1]);
		}
		waitpid(pid, &stat, 0);
		return (false);
	}
	if (index > 1)
	{
		dup2(pipe_fd[0], STDIN_FILENO);
		close(pipe_fd[1]);
		close(pipe_fd[0]);
	}
	dup2(out_fd, STDOUT_FILENO);
	close(out_fd);
	if (commands[index - 1].type == COMMAND_SUBSHELL)
	{
		_handle_redirect_list(((t_subshell *)commands[index - 1].command)->redirect_list);
		_exec_exec(ctx, ((t_subshell *)commands)[index - 1].and_or, &error);
		exit(ctx->env_ctx->current_code); // WARNING: Will leak parser ctx...
	}
	_handle_redirect_list(((t_simple_command *)commands[index - 1].command)->redirect_list);
	if (_run_command(((t_simple_command *)commands[index - 1].command)->pn,
		(const char **)((t_simple_command *)commands[index - 1].command)->args->args,
		&ctx->env_ctx->env) == MS_PERM_DENIED)
		exit(MS_PERM_DENIED);
	// Test for builtins
	exit(MS_COMMAND_NOT_FOUND);
}

bool	_exec_pipeline(
			t_exec_ctx *ctx,
			const t_pipeline *pipeline,
			t_ms_error *error)
{
	pid_t	pid;
	int		stat;
	int		pipe_fd[2];

	if (pipeline->used == 1)
	{
		// test for builtins
	}
	else
		pipe(pipe_fd);
	pid = fork();
	if (pid > 0)
	{
		if (pipeline->used > 1)
		{
			close(pipe_fd[0]);
			__exec_pipeline(ctx, pipeline->commands, pipeline->used - 1, pipe_fd[1]);
		}
		waitpid(pid, &stat, 0);
		return (false);
	}
	if (pipeline->used > 1)
	{
		close(pipe_fd[1]);
		dup2(pipe_fd[0], STDIN_FILENO);
		close(pipe_fd[0]);
	}
	if (pipeline->commands[pipeline->used - 1].type == COMMAND_SUBSHELL)
	{
		_handle_redirect_list(((t_subshell *)pipeline->commands[pipeline->used - 1].command)->redirect_list);
		_exec_exec(ctx, ((t_subshell *)pipeline->commands[pipeline->used - 1].command)->and_or, error);
		exit(ctx->env_ctx->current_code); // WARNING: Will leak parser ctx...
	}
	_handle_redirect_list(((t_simple_command *)pipeline->commands[pipeline->used - 1].command)->redirect_list);
	if (_run_command(((t_simple_command *)pipeline->commands[pipeline->used - 1].command)->pn,
		(const char **)((t_simple_command *)pipeline->commands[pipeline->used - 1].command)->args->args,
		&ctx->env_ctx->env) == MS_PERM_DENIED)
		exit(MS_PERM_DENIED);
	// Test for builtins
	exit(MS_COMMAND_NOT_FOUND);
}

bool	_exec_exec(
			t_exec_ctx *ctx,
			const t_and_or *and_or,
			t_ms_error *error
			)
{
	bool			should_stop;
	t_logic_type	logic_type;
	int				*current_code;

	if (and_or->left != NULL)
		if (_exec_exec(ctx, and_or->left, error))
			return (true);
	should_stop = false;
	logic_type = and_or->logic_type;
	current_code = &ctx->env_ctx->current_code;
	if (and_or->left == NULL
		|| (*current_code == MS_STATUS_OK) ^ (logic_type == LOGIC_OR))
		should_stop = _exec_pipeline(ctx, and_or->right_pipeline, error);
	return (should_stop || *error != MS_OK);
}
