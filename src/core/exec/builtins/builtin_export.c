/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amassias <amassias@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 13:13:49 by amassias          #+#    #+#             */
/*   Updated: 2024/03/05 19:27:16 by amassias         ###   ########.fr       */
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

static bool			_export_var(
						t_ms_error *error_ptr,
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
		return (_show_envp(ctx, envp));
	++argv;
	should_fail = false;
	while (*argv)
	{
		if (_export_var(&error, ctx, *argv++))
		{
			should_fail = true;
			continue ;
		}
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

static bool	_is_valid_id(
				const char *id,
				const char *end
				)
{
	if (end == NULL)
		end = id + ft_strlen(id);
	if (id >= end)
		return (false);
	if (!ft_isalpha(*id++))
		return (false);
	while (id < end)
	{
		if (!ft_isalnum(*id) && *id != '_')
			return (false);
		++id;
	}
	return (true);
}

static bool	_export_var(
				t_ms_error *error_ptr,
				t_exec_ctx *ctx,
				const char *var
				)
{
	char		*eq;

	eq = ft_strchr(var, '=');
	if (!_is_valid_id(var, eq))
		return (dprintf(STDERR_FILENO, ERROR_NOT_VALID_ID "\n", var), true);
	if (eq != NULL)
	{
		*eq = '\0';
		*error_ptr = env_set_var(&ctx->env_ctx->env, var, eq + 1);
		*eq = '=';
	}
	else
		*error_ptr = env_set_var(&ctx->env_ctx->env, var, "");
	return (false);
}
