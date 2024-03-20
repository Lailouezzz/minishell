/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amassias <amassias@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 13:13:49 by amassias          #+#    #+#             */
/*   Updated: 2024/03/20 13:38:45 by amassias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file builtin_cd.c
 * @author Antoine Massias (amassias@student.42lehavre.fr)
 * @date 2024-02-21
 * @copyright Copyright (c) 2024
 */

/* ************************************************************************** */
/*                                                                            */
/* Includes                                                                   */
/*                                                                            */
/* ************************************************************************** */

#include "core/builtins.h"

#include <libft.h>
#include <stdbool.h>
#include <stdio.h>

/* ************************************************************************** */
/*                                                                            */
/* Defines                                                                    */
/*                                                                            */
/* ************************************************************************** */

#define ENV_VAR_PWD "PWD"
#define ENV_VAR_PWD_OLD "OLDPWD"
#define ENV_VAR_HOME "HOME"

#define MS_CD "minishell: cd: "

#define ERROR_NO_OLDPWD "OLDPWD not set"
#define ERROR_NO_HOME "HOME not set"
#define ERROR_TO_MANY_ARGS "too many arguments"
#define ERROR_NOT_ENOUGH_ARGS "not enough arguments"

/* ************************************************************************** */
/*                                                                            */
/* Helper prototypes                                                          */
/*                                                                            */
/* ************************************************************************** */

static size_t		_count_args(
						char **argv
						);

static t_ms_error	_update_pwd_vars(
						t_exec_ctx *ctx,
						const char *pwd,
						const char *old_pwd
						);

static t_ms_error	_change_pwd(
						t_exec_ctx *ctx,
						const char *dir
						);

/* ************************************************************************** */
/*                                                                            */
/* Header implementation                                                      */
/*                                                                            */
/* ************************************************************************** */

t_ms_error	builtin_cd(
				t_exec_ctx *ctx,
				char **argv,
				char __attribute__((unused)) **envp
				)
{
	const size_t	count = _count_args(argv);
	const char		*home;

	if (count == 2)
		return (_change_pwd(ctx, argv[1]));
	if (count > 2)
		return (dprintf(STDERR_FILENO, MS_CD ERROR_TO_MANY_ARGS "\n"),
			env_set_code(ctx->env_ctx, 1));
	home = env_ctx_get_variable(ctx->env_ctx, ENV_VAR_HOME);
	if (home == NULL)
		return (dprintf(STDERR_FILENO, MS_CD ERROR_NO_HOME "\n"),
			env_set_code(ctx->env_ctx, 1));
	return (_change_pwd(ctx, home));
}

/* ************************************************************************** */
/*                                                                            */
/* helper implementation                                                      */
/*                                                                            */
/* ************************************************************************** */

static size_t	_count_args(
					char **argv
					)
{
	size_t	count;

	count = 0;
	while (argv[count])
		++count;
	return (count);
}

static t_ms_error	_update_pwd_vars(
						t_exec_ctx *ctx,
						const char *pwd,
						const char *old_pwd
						)
{
	t_ms_error	error;

	error = env_set_var(&ctx->env_ctx->env, ENV_VAR_PWD, pwd);
	if (error != MS_OK)
		return (error);
	return (env_set_var(&ctx->env_ctx->env, ENV_VAR_PWD_OLD, old_pwd));
}

static const char	*_chose_dir(
						t_env_ctx *ctx,
						const char *dir
						)
{
	if (ft_strcmp(dir, "-") != 0)
		return (dir);
	dir = env_ctx_get_variable(ctx, ENV_VAR_PWD_OLD);
	if (dir == NULL)
		dprintf(STDERR_FILENO, MS_CD ERROR_NO_OLDPWD "\n");
	return (dir);
}

static t_ms_error	_change_pwd(
						t_exec_ctx *ctx,
						const char *dir
						)
{
	const bool	rollback = ft_strcmp(dir, "-") == 0;
	t_ms_error	error;
	char		*old_pwd;

	dir = _chose_dir(ctx->env_ctx, dir);
	if (dir == NULL)
		return (env_set_code(ctx->env_ctx, 1));
	old_pwd = getcwd(NULL, 0);
	if (old_pwd == NULL)
		return (env_set_code(ctx->env_ctx, 1), MS_BAD_ALLOC);
	if (chdir(dir) == -1)
	{
		(dprintf(STDERR_FILENO, MS_CD), perror(dir));
		return (free(old_pwd), env_set_code(ctx->env_ctx, 1));
	}
	error = _update_pwd_vars(ctx, dir, old_pwd);
	if (rollback && error == MS_OK)
		dprintf(STDOUT_FILENO, "%s\n",
			env_ctx_get_variable(ctx->env_ctx, ENV_VAR_PWD));
	return (env_set_code(ctx->env_ctx, 0), free(old_pwd), error);
}
