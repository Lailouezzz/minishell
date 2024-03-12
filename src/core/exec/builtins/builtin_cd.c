/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amassias <amassias@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 13:13:49 by amassias          #+#    #+#             */
/*   Updated: 2024/03/12 20:26:13 by amassias         ###   ########.fr       */
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

#define ERROR_TO_MANY_ARGS "minishell: cd: too many arguments"
#define ERROR_NOT_ENOUGH_ARGS "minishell: cd: not enough arguments"
#define ERROR_NO_FILE "minishell: cd: %s: No such file or directory"
#define ERROR_CANT_CHANGE_DIR "minishell: cd: %s: couldn't change directory"

/* ************************************************************************** */
/*                                                                            */
/* Helper prototypes                                                          */
/*                                                                            */
/* ************************************************************************** */

static size_t		_count_args(
						char **argv
						);

static t_ms_error	_update_pwd(
						t_exec_ctx *ctx
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
	size_t	count;
	int		code;

	count = _count_args(argv);
	if (count != 2)
	{
		ctx->env_ctx->current_code = 1;
		if (count > 2)
			dprintf(STDERR_FILENO, ERROR_TO_MANY_ARGS "\n");
		else
			dprintf(STDERR_FILENO, ERROR_NOT_ENOUGH_ARGS "\n");
		return (env_set_code(ctx->env_ctx, 1));
	}
	code = chdir(argv[1]) == -1;
	if (code != 0)
		(dprintf(STDERR_FILENO, "minishell: cd: "), perror(argv[1]));
	if (_update_pwd(ctx))
		return (env_set_code(ctx->env_ctx, 1), MS_FATAL);
	return (env_set_code(ctx->env_ctx, code));
}

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

static t_ms_error	_update_pwd(
						t_exec_ctx *ctx
						)
{
	char	*buf;

	buf = getcwd(NULL, 0);
	if (buf == NULL)
		return (MS_FATAL);
	env_set_var(&ctx->env_ctx->env, "PWD", buf);
	free(buf);
	return (MS_OK);
}
