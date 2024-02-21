/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amassias <amassias@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 13:13:49 by amassias          #+#    #+#             */
/*   Updated: 2024/02/21 15:06:19 by amassias         ###   ########.fr       */
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
#define ERROR_CANT_CHANGE_DIR "minishell: cd: %s: could change directory"

/* ************************************************************************** */
/*                                                                            */
/* Header implementation                                                      */
/*                                                                            */
/* ************************************************************************** */

t_ms_error	builtin_cd(
				t_exec_ctx *ctx,
				char **argv,
				char **envp
				)
{
	size_t	count;
	int		code;

	(void)envp;
	count = 0;
	while (argv[count])
		++count;
	if (count != 2)
	{
		ctx->env_ctx->current_code = 1;
		if (count > 2)
			dprintf(STDERR_FILENO, ERROR_TO_MANY_ARGS "\n");
		else
			dprintf(STDERR_FILENO, ERROR_NOT_ENOUGH_ARGS "\n");
		return (env_set_code(ctx->env_ctx, 1));
	}
	if (access(argv[1], F_OK) != 0)
	{
		dprintf(STDERR_FILENO, ERROR_NO_FILE "\n", argv[1]);
		return (env_set_code(ctx->env_ctx, 1));
	}
	code = chdir(argv[1]) == -1;
	if (code != 0)
		dprintf(STDERR_FILENO, ERROR_CANT_CHANGE_DIR "\n", argv[1]);
	return (env_set_code(ctx->env_ctx, code));
}
