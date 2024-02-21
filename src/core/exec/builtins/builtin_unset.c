/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amassias <amassias@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 13:13:49 by amassias          #+#    #+#             */
/*   Updated: 2024/02/21 16:40:33 by amassias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file builtin_unset.c
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

#define ERROR_NOT_VALID_ID "minishell: export: '%s': not a valid identifier"

/* ************************************************************************** */
/*                                                                            */
/* Helper protoypes                                                           */
/*                                                                            */
/* ************************************************************************** */

static bool	_input_ok(
				const char *var
				);

/* ************************************************************************** */
/*                                                                            */
/* Header implementation                                                      */
/*                                                                            */
/* ************************************************************************** */

t_ms_error	builtin_unset(
				t_exec_ctx *ctx,
				char **argv,
				char **envp
				)
{
	t_ms_error	error;
	bool		should_fail;

	(void)envp;
	should_fail = false;
	while (*argv)
	{
		if (!_input_ok(*argv))
		{
			dprintf(STDERR_FILENO, ERROR_NOT_VALID_ID "\n", *argv++);
			should_fail = true;
			continue ;
		}
		error = env_unset_var(&ctx->env_ctx->env, *argv++);
		if (error)
			return (env_set_code(ctx->env_ctx, -1), error);
	}
	return (env_set_code(ctx->env_ctx, should_fail));
}

/* ************************************************************************** */
/*                                                                            */
/* Helper implementation                                                      */
/*                                                                            */
/* ************************************************************************** */

static bool	_input_ok(
				const char *var
				)
{
	if (!ft_isalpha(*var++))
		return (false);
	while (*var)
		if (!ft_isalnum(*var++))
			return (false);
	return (true);
}