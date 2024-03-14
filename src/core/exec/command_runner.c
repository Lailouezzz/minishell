/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_runner.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amassias <amassias@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 16:53:56 by amassias          #+#    #+#             */
/*   Updated: 2024/03/14 13:43:04 by amassias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file command_runner.c
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

/* ************************************************************************** */
/*                                                                            */
/* Defines                                                                    */
/*                                                                            */
/* ************************************************************************** */

#define ERR_NO_FILE_OR_DIR "%s: No such file or directory"

/* ************************************************************************** */
/*                                                                            */
/* Helper protoypes                                                           */
/*                                                                            */
/* ************************************************************************** */

static char			**_get_paths(
						t_env_ctx *ctx
						);

static t_ms_error	_run_builtin(
						t_exec_ctx *ctx,
						const char *program_name,
						const char **args
						);

static t_ms_error	_run_command_with_cwd(
						t_env_ctx *ctx,
						const char *program_name,
						const char **args
						);

static t_ms_error	_run_command_with_path(
						t_env_ctx *ctx,
						const char *program_name,
						const char **args
						);

/* ************************************************************************** */
/*                                                                            */
/* Header implementation                                                      */
/*                                                                            */
/* ************************************************************************** */

t_ms_error	run_command(
				t_exec_ctx *ctx,
				const char *program_name,
				const char **args
				)
{
	t_ms_error	error;

	error = _run_builtin(ctx, program_name, args);
	if (error != MS_COMMAND_NOT_FOUND)
		return (error);
	error = launch_command(ctx->env_ctx, program_name, "", args);
	if (error != MS_COMMAND_NOT_FOUND)
		return (error);
	error = _run_command_with_cwd(ctx->env_ctx, program_name, args);
	if (error != MS_COMMAND_NOT_FOUND)
		return (error);
	error = _run_command_with_path(ctx->env_ctx, program_name, args);
	if (error != MS_COMMAND_NOT_FOUND)
		return (error);
	if (ft_strchr(program_name, '/'))
		dprintf(STDERR_FILENO, MS ERR_NO_FILE_OR_DIR "\n", program_name);
	else
		dprintf(STDERR_FILENO, ERR_CMD_NOT_FOUND "\n", program_name);
	return (MS_COMMAND_NOT_FOUND);
}

/* ************************************************************************** */
/*                                                                            */
/* Helper implementation                                                      */
/*                                                                            */
/* ************************************************************************** */

static char	**_get_paths(
				t_env_ctx *ctx
				)
{
	const char	*path = env_ctx_get_variable(ctx, "PATH");

	if (path)
		return (ft_split(path, ':'));
	return (ft_split("", ':'));
}

static t_ms_error	_run_builtin(
						t_exec_ctx *ctx,
						const char *program_name,
						const char **args
						)
{
	size_t			i;

	i = 0;
	while (i < BUILTIN_COUNT)
	{
		if (ft_strcmp(program_name, g_builtins[i++].name) != 0)
			continue ;
		g_builtins[i - 1].fun(ctx,
			(char **)args, (char **)ctx->env_ctx->env.env_vars);
		close(STDIN_FILENO);
		close(STDOUT_FILENO);
		exec_cleanup_exit(ctx, ctx->env_ctx->current_code);
	}
	return (MS_COMMAND_NOT_FOUND);
}

static t_ms_error	_run_command_with_cwd(
						t_env_ctx *ctx,
						const char *program_name,
						const char **args
						)
{
	char		*cwd;
	t_ms_error	error;

	if (ft_strchr(program_name, '/') == NULL)
		return (MS_COMMAND_NOT_FOUND);
	cwd = getcwd(NULL, 0);
	if (cwd == NULL)
		return (MS_BAD_ALLOC);
	error = launch_command(ctx, program_name, cwd, args);
	free(cwd);
	return (error);
}

static t_ms_error	_run_command_with_path(
						t_env_ctx *ctx,
						const char *program_name,
						const char **args
						)
{
	char		**paths;
	char		**itr;
	t_ms_error	error;

	paths = _get_paths(ctx);
	if (paths == NULL)
		return (MS_BAD_ALLOC);
	itr = paths;
	while (*itr)
	{
		error = launch_command(ctx, program_name, *itr++, args);
		if (error != MS_COMMAND_NOT_FOUND)
			return (u_free_list((void ***)&paths), error);
	}
	u_free_list((void ***)&paths);
	return (MS_COMMAND_NOT_FOUND);
}
