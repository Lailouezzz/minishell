/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-boud <ale-boud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 15:34:01 by amassias          #+#    #+#             */
/*   Updated: 2024/02/29 15:01:59 by ale-boud         ###   ########.fr       */
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
#include "core/builtins.h"

#include <fcntl.h>
#include <sys/signal.h>
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

#define PERM_DENIED_MSG "minishell: permission denied: %s\n"

/* ************************************************************************** */
/*                                                                            */
/* Helper protoypes                                                           */
/*                                                                            */
/* ************************************************************************** */

static const char		*_get_end(
							const char *str
							);

static int				_create_heredoc(
							const char *delim
							);

static int				_open_redirection(
							t_io_info *io_info
							);

static void				_handle_redirect_list(
							const t_redirect_list *list
							);

static char				*_as_full_path(
							const char *file,
							const char *path
							);

static char				**_get_paths(
							t_env_ctx *ctx
							);

static void				_free_list(
							void ***list_ptr
							);

static t_ms_error		__run_command(
							const char *program_name,
							const char *path,
							const char **args,
							const char **envp
							);

static t_ms_error		_run_command(
							t_exec_ctx *ctx,
							const char *program_name,
							const char **args,
							const char **envp
							);

static t_ms_error		__exec_pipeline_simple_command(
							t_exec_ctx *ctx,
							t_simple_command *command
							);

static t_ms_error		__exec_pipeline_subshell(
							t_exec_ctx *ctx,
							t_subshell *command
							);

static noreturn void	_quit(
							t_exec_ctx *ctx,
							t_ms_error error
							);

static noreturn void	_child(
							size_t index,
							int fds[3],
							t_command *commands,
							t_exec_ctx *ctx
							);

static t_ms_error		__exec_pipeline(
							t_exec_ctx *ctx,
							t_command *commands,
							size_t index,
							int out_fd
							);

static t_ms_error		_exec_pipeline_parent(
							t_exec_ctx *ctx,
							const t_pipeline *pipeline,
							pid_t pid,
							int pipe_fd[2]
							);

static bool				_test_builtin(
							t_exec_ctx *ctx,
							t_simple_command *command,
							t_ms_error *error
							);

static bool				_exec_pipeline(
							t_exec_ctx *ctx,
							const t_pipeline *pipeline,
							t_ms_error *error
							);

static bool				_exec_exec(
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

static const char	*_get_end(
						const char *str
						)
{
	const char	*end;

	end = ft_strchr(str, '\n');
	if (end == NULL)
		end = ft_strchr(str, '\0');
	return (end);
}

static int	_create_heredoc(
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

static int	_open_redirection(
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
	else
		fd = _create_heredoc(io_info->file);
	return (fd);
}

// TODO: return error code ?
// TODO: Handle case where `fd == -1`
static void	_handle_redirect_list(
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
			exit(-1);
		if (info[i].io_type == IO_IN || info[i].io_type == IO_HEREDOC)
			dup2(fd, STDIN_FILENO);
		else
			dup2(fd, STDOUT_FILENO);
		close(fd);
		++i;
	}
}

static char	*_as_full_path(
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

static char	**_get_paths(
				t_env_ctx *ctx
				)
{
	const char	*path = env_ctx_get_variable(ctx, "PATH");

	if (path)
		return (ft_split(path, ':'));
	return (ft_split("", ':'));
}

static void	_free_list(
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

static t_ms_error	__run_command(
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
	{
		dprintf(STDERR_FILENO, PERM_DENIED_MSG, program_name);
		free(abolute_path);
		return (MS_PERM_DENIED);
	}
	execve(abolute_path, (char **)args, (char **)envp);
	free(abolute_path);
	return (MS_FATAL);
}

static t_ms_error	_run_command(
						t_exec_ctx *ctx,
						const char *program_name,
						const char **args,
						const char **envp
						)
{
	char		**paths;
	char		**itr;
	char		*cwd;
	t_ms_error	error;

	cwd = getcwd(NULL, 0);
	if (cwd == NULL)
		return (MS_BAD_ALLOC);
	error = __run_command(program_name, cwd, args, envp);
	free(cwd);
	if (error != MS_OK)
		return (error);
	paths = _get_paths(ctx->env_ctx);
	if (paths == NULL)
		return (MS_BAD_ALLOC);
	itr = paths;
	while (*itr)
	{
		error = __run_command(program_name, *itr++, args, envp);
		if (error != MS_OK)
			return (_free_list((void ***)&paths), error);
	}
	dprintf(STDERR_FILENO, "minishell: command not found: %s\n", program_name);
	return (_free_list((void ***)&paths), MS_COMMAND_NOT_FOUND);
}

static t_ms_error	__exec_pipeline_simple_command(
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

static t_ms_error	__exec_pipeline_subshell(
						t_exec_ctx *ctx,
						t_subshell *command
						)
{
	t_ms_error	error;

	_handle_redirect_list(command->redirect_list);
	_exec_exec(ctx, command->and_or, &error);
	return (error);
}

static noreturn void	_quit(
							t_exec_ctx *ctx,
							t_ms_error error
							)
{
	t_ms_status	status;

	status = ctx->env_ctx->current_code;
	if (error == MS_FATAL)
	{
		ft_putendl_fd("minishell: internal error", STDERR_FILENO);
		status = MS_STATUS_FAILURE;
	}
	else if (error == MS_BAD_ALLOC)
	{
		ft_putendl_fd("minishell: out of resources", STDERR_FILENO);
		status = MS_STATUS_FAILURE;
	}
	else if (error == MS_COMMAND_NOT_FOUND)
		status = MS_STATUS_COMMAND_NOT_FOUND;
	else if (error == MS_PERM_DENIED)
		status = MS_STATUS_PERM_DENIED;
	exec_cleanup_exit(ctx, status);
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
		_quit(ctx, __exec_pipeline_subshell(ctx, commands[index].command));
	_quit(ctx, __exec_pipeline_simple_command(ctx, commands[index].command));
}

static void	_wait_child(
						t_exec_ctx *ctx,
						pid_t pid
						)
{
	int	stat;

	waitpid(pid, &stat, 0);
	env_set_code(ctx->env_ctx, WEXITSTATUS(stat));
	if (WIFSIGNALED(stat))
		env_set_code(ctx->env_ctx, 128 + WTERMSIG(stat));
}

// TODO: do something about the parser leaking each time an error occurs
static t_ms_error	__exec_pipeline(
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
	if (index > 0)
		(void)(pipe(pipe_fd) == 0);
	if (g_signo == SIGINT)
	{
		if (index > 0)
			(close(pipe_fd[0]), close(pipe_fd[1]), close(out_fd));
		return (MS_OK);
	}
	pid = fork();
	if (pid == -1)
	{
		if (index > 0)
			(close(pipe_fd[0]), close(pipe_fd[1]), close(out_fd));
		return (MS_FATAL);
	}
	if (pid == 0)
		_child(index, (int [3]){pipe_fd[0], pipe_fd[1], out_fd}, commands, ctx);
	close(out_fd);
	if (index > 0)
		(close(pipe_fd[0]), __exec_pipeline(ctx, commands, index, pipe_fd[1]));
	waitpid(pid, &status, 0);
	return (MS_OK);
}

static t_ms_error	_exec_pipeline_parent(
						t_exec_ctx *ctx,
						const t_pipeline *pipeline,
						pid_t pid,
						int pipe_fd[2]
						)
{
	t_ms_error	error;

	error = MS_OK;
	if (pipeline->used > 1)
	{
		close(pipe_fd[0]);
		error = __exec_pipeline(ctx, pipeline->commands,
				pipeline->used - 1, pipe_fd[1]);
	}
	_wait_child(ctx, pid);
	return (error);
}

static bool	_test_builtin(
				t_exec_ctx *ctx,
				t_simple_command *command,
				t_ms_error *error
				)
{
	(void)ctx;
	(void)command;
	(void)error;
	return (false);
}

static bool	_exec_pipeline(
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
		if (_test_builtin(ctx, pipeline->commands[0].command, error))
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
	*error = _exec_pipeline_parent(ctx, pipeline, pid, pipe_fd);
	return (*error != MS_OK);
}

static bool	_exec_exec(
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
	return (should_stop || *error != MS_OK || g_signo == SIGINT);
}
