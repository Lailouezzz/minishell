/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amassias <amassias@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 13:13:49 by amassias          #+#    #+#             */
/*   Updated: 2024/02/21 16:35:17 by amassias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file builtin_export.c
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

static int			_string_comparator(
						const char	**a_ptr,
						const char	**b_ptr
						);

static t_ms_error	_show_envp(
						t_exec_ctx *ctx,
						char **envp
						);

static t_ms_error	_export_var(
						t_exec_ctx *ctx,
						const char *var
						);

/* ************************************************************************** */
/*                                                                            */
/* Header implementation                                                      */
/*                                                                            */
/* ************************************************************************** */

t_ms_error	builtin_export(
				t_exec_ctx *ctx,
				char **argv,
				char **envp
				)
{
	bool		should_fail;
	t_ms_error	error;

	if (argv[1] == NULL)
		return (env_set_code(ctx->env_ctx, -1), _show_envp(ctx, envp));
	should_fail = false;
	while (*argv)
	{
		if (!ft_isalpha(**argv))
		{
			dprintf(STDERR_FILENO, ERROR_NOT_VALID_ID "\n", *argv++);
			should_fail = true;
			continue ;
		}
		error = _export_var(ctx, *argv++);
		if (error != MS_OK)
			return (env_set_code(ctx->env_ctx, -1), error);
	}
	return (env_set_code(ctx->env_ctx, should_fail));
}

/* ************************************************************************** */
/*                                                                            */
/* Helper implementation                                                      */
/*                                                                            */
/* ************************************************************************** */

static int	_string_comparator(
				const char	**a_ptr,
				const char	**b_ptr
				)
{
	const char	*a;
	const char	*b;

	a = *a_ptr;
	b = *b_ptr;
	while (*a)
	{
		if (*(const unsigned char *)a != *(const unsigned char *)b)
			break ;
		a++;
		b++;
	}
	return (*(const char *)a - *(const char *)b);
}

static t_ms_error	_show_envp(
				t_exec_ctx *ctx,
				char **envp
				)
{
	size_t	count;
	size_t	i;
	char	**sorted;

	(void) ctx;
	count = 0;
	while (envp[count])
		++count;
	sorted = (char **) malloc(sizeof(char *) * count);
	if (sorted == NULL)
		return (MS_BAD_ALLOC);
	ft_memcpy(sorted, envp, sizeof(char *) * count);
	ft_qsort(sorted, count, sizeof(char *), (t_comparator)_string_comparator);
	i = 0;
	while (i < count)
		printf("%s\n", sorted[i++]);
	free(sorted);
	return (env_set_code(ctx->env_ctx, 0));
}

static t_ms_error	_export_var(
						t_exec_ctx *ctx,
						const char *var
						)
{
	char		*eq;
	t_ms_error	error;

	eq = ft_strchr(var, '=');
	if (eq == NULL)
		return (env_set_var(&ctx->env_ctx->env, var, ""));
	*eq = '\0';
	error = env_set_var(&ctx->env_ctx->env, var, eq + 1);
	*eq = '=';
	return (error);
}
