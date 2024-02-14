/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amassias <amassias@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 15:34:01 by amassias          #+#    #+#             */
/*   Updated: 2024/02/14 16:57:20 by amassias         ###   ########.fr       */
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

int	_open_redirection(
		t_io_info *io_info
		)
{
	int	fd;

	if (io_info->io_type == IO_IN)
		fd = open(io_info->file, O_IN);
	else if (io_info->io_type == IO_OUT)
		fd = open(io_info->file, O_OT, 0666);
	else if (io_info->io_type == IO_APPEND)
		fd = open(io_info->file, O_AP, 0666);
	else // if (io_info->io_type == IO_HEREDOC)
		fd = _create_heredoc(io_info->file);
	return (fd);
}

// TODO: return error code ?
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
		fd = _open_redirection(&info[i]);
		if (fd == -1)
			exit(-1); // TODO: Handle case where `fd == -1`
		if (info[i].io_type == IO_IN || info[i].io_type == IO_HEREDOC)
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

const char	*_get_pwd(
			const char **vars
			)
{
	while (*vars)
	{
		if (ft_strncmp(*vars, "PWD=", 4) == 0)
			return (*vars + 4);
		++vars;
	}
	return ("");
	// (void)vars;
	// return ("/home/amassias/Documents/minishell");
}

void	_free_list(
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

t_ms_error	__run_command(
				const char *program_name,
				const char *path,
				const char **args,
				const char **envp
				)
{
	char	*abolute_path;

	abolute_path = _as_full_path(program_name, path);
	if (access(abolute_path, F_OK) != 0)
		return (free(abolute_path), MS_OK);
	if (access(abolute_path, X_OK) != 0)
		return (free(abolute_path), MS_PERM_DENIED);
	execve(abolute_path, (char **)args, (char **)envp);
	return (free(abolute_path), MS_FATAL);
}

t_ms_error	_run_command(
				t_exec_ctx *ctx,
				const char *program_name,
				const char **args,
				const char **envp
				)
{
	char		**paths;
	char		**itr;
	t_ms_error	error;

	paths = _get_paths(&ctx->env_ctx->env);
	error = __run_command(program_name, _get_pwd(envp),
			(const char **)args, (const char **)envp);
	if (error != MS_OK)
		return (error);
	itr = paths;
	while (*itr)
	{
		error = __run_command(program_name, *itr++,
				(const char **)args, (const char **)envp);
		if (error != MS_OK)
			return (error);
	}
	_free_list((void ***)&paths);
	return (MS_COMMAND_NOT_FOUND);
}

t_ms_error	__exec_pipeline_simple_command(
				t_exec_ctx *ctx,
				t_simple_command *command
				)
{
	t_ms_error	error;

	_handle_redirect_list(command->redirect_list);
	error = _run_command(
			ctx,
			command->pn,
			(const char **)command->args->args,
			(const char **)ctx->env_ctx->env.env_vars);
	return (error);
}

t_ms_error	__exec_pipeline_subshell(
				t_exec_ctx *ctx,
				t_subshell *command
				)
{
	t_ms_error	error;

	_handle_redirect_list(command->redirect_list);
	_exec_exec(ctx, command->and_or, &error);
	return (error);
}

// TODO: do something about the parser leaking each time an error occurs
t_ms_error	__exec_pipeline(
				t_exec_ctx *ctx,
				t_command *commands,
				size_t index,
				int out_fd
			)
{
	pid_t		pid;
	int			stat;
	int			pipe_fd[2];

	if (index-- == 0)
		return (MS_OK);
	if (index > 0)
		pipe(pipe_fd);
	pid = fork();
	if (pid == -1)
		return (MS_FATAL);
	if (pid != 0)
	{
		close(out_fd);
		if (index > 0)
		{
			close(pipe_fd[0]);
			__exec_pipeline(ctx, commands, index, pipe_fd[1]);
		}
		waitpid(pid, &stat, 0);
		env_set_code(ctx->env_ctx, WEXITSTATUS(stat));
		if (WIFSIGNALED(stat))
			env_set_code(ctx->env_ctx, MS_STATUS_COMMAND_NOT_FOUND + WTERMSIG(stat));
		return (false);
	}
	if (index > 0)
	{
		dup2(pipe_fd[0], STDIN_FILENO);
		close(pipe_fd[1]);
		close(pipe_fd[0]);
	}
	dup2(out_fd, STDOUT_FILENO);
	close(out_fd);
	if (commands[index].type == COMMAND_SUBSHELL)
		exit(__exec_pipeline_subshell(ctx, commands[index].command));
	exit(__exec_pipeline_simple_command(ctx, commands[index].command));
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
			*error = __exec_pipeline(ctx, pipeline->commands, pipeline->used - 1, pipe_fd[1]);
		}
		waitpid(pid, &stat, 0);
		env_set_code(ctx->env_ctx, WEXITSTATUS(stat));
		if (WIFSIGNALED(stat))
			env_set_code(ctx->env_ctx, MS_STATUS_COMMAND_NOT_FOUND + WTERMSIG(stat));
		return (false);
	}
	if (pipeline->used > 1)
	{
		close(pipe_fd[1]);
		dup2(pipe_fd[0], STDIN_FILENO);
		close(pipe_fd[0]);
	}
	if (pipeline->commands[pipeline->used - 1].type == COMMAND_SUBSHELL)
		exit(__exec_pipeline_subshell(ctx, pipeline->commands[pipeline->used - 1].command));
	exit(__exec_pipeline_simple_command(ctx, pipeline->commands[pipeline->used - 1].command));
	// Test for builtins
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
