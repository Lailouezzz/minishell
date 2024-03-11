/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_launcher.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amassias <amassias@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 17:11:05 by amassias          #+#    #+#             */
/*   Updated: 2024/03/11 17:32:50 by amassias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file command_launcher.c
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

#include <sys/stat.h>

/* ************************************************************************** */
/*                                                                            */
/* Global variables                                                           */
/*                                                                            */
/* ************************************************************************** */

static const char	*g_file_status_error_msg[] = {
[FILE_STATUS_NOT_FOUND] = "%s: command not found\n",
[FILE_STATUS_DIRECTORY] = MS "%s: Is a directory\n",
[FILE_STATUS_PERM_DENIED] = MS "%s: Permission denied\n",
};

static t_ms_error	g_file_status_to_error[] = {
[FILE_STATUS_NOT_FOUND] = MS_COMMAND_NOT_FOUND,
[FILE_STATUS_DIRECTORY] = MS_COMMAND_IS_DIRECTORY,
[FILE_STATUS_PERM_DENIED] = MS_PERM_DENIED,
};

static t_ms_status	g_file_status_to_exit_code[] = {
[FILE_STATUS_NOT_FOUND] = MS_STATUS_COMMAND_NOT_FOUND,
[FILE_STATUS_DIRECTORY] = MS_STATUS_PERM_DENIED,
[FILE_STATUS_PERM_DENIED] = MS_STATUS_PERM_DENIED,
};

/* ************************************************************************** */
/*                                                                            */
/* Helper protoypes                                                           */
/*                                                                            */
/* ************************************************************************** */

static char			*_as_full_path(
						const char *file,
						const char *path
						);

static t_ms_error	_file_status_error(
						t_env_ctx *ctx,
						t_file_status status,
						const char *program_name
						);

static bool			_is_valid_exec(
						const char *absolute_path,
						t_file_status *status_ptr
						);

/* ************************************************************************** */
/*                                                                            */
/* Header implementation                                                      */
/*                                                                            */
/* ************************************************************************** */

t_ms_error	launch_command(
				t_env_ctx *ctx,
				const char *program_name,
				const char *path,
				const char **args
				)
{
	char			*abolute_path;
	t_file_status	status;

	abolute_path = _as_full_path(program_name, path);
	if (abolute_path == NULL)
		return (MS_FATAL);
	if (_is_valid_exec(abolute_path, &status))
		return (free(abolute_path), MS_FATAL);
	if (status == FILE_STATUS_NOT_FOUND)
		return (free(abolute_path), MS_COMMAND_NOT_FOUND);
	if (status != FILE_STATUS_OK)
		return (free(abolute_path),
			_file_status_error(ctx, status, program_name));
	execve(abolute_path, (char **)args, (char **)ctx->env.env_vars);
	free(abolute_path);
	return (MS_FATAL);
}

/* ************************************************************************** */
/*                                                                            */
/* Helper implementation                                                      */
/*                                                                            */
/* ************************************************************************** */

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

static t_ms_error	_file_status_error(
						t_env_ctx *ctx,
						t_file_status status,
						const char *program_name
						)
{
	t_ms_error	error;

	dprintf(STDERR_FILENO, g_file_status_error_msg[status], program_name);
	error = env_set_code(ctx, g_file_status_to_exit_code[status]);
	if (error)
		return (error);
	return (g_file_status_to_error[status]);
}

static bool	_is_valid_exec(
				const char *absolute_path,
				t_file_status *status_ptr
				)
{
	struct stat	status;

	if (access(absolute_path, F_OK))
		return (*status_ptr = FILE_STATUS_NOT_FOUND, false);
	if (stat(absolute_path, &status) != 0)
		return (true);
	if (!S_ISREG(status.st_mode))
		return (*status_ptr = FILE_STATUS_DIRECTORY, false);
	if (!(status.st_mode & S_IXUSR))
		return (*status_ptr = FILE_STATUS_PERM_DENIED, false);
	return (*status_ptr = FILE_STATUS_OK, false);
}
