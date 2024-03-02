/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amassias <amassias@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 13:13:49 by amassias          #+#    #+#             */
/*   Updated: 2024/03/02 17:18:44 by amassias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file builtin_exit.c
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
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>

/* ************************************************************************** */
/*                                                                            */
/* Helper protoypes                                                           */
/*                                                                            */
/* ************************************************************************** */

static bool	_read_arg(
				const char *str,
				int *code
				);

/* ************************************************************************** */
/*                                                                            */
/* Header implementation                                                      */
/*                                                                            */
/* ************************************************************************** */

t_ms_error	builtin_exit(
				t_exec_ctx *ctx,
				char **argv,
				char **envp
				)
{
	int	code;

	(void)envp;
	dprintf(STDERR_FILENO, "exit\n");
	if (argv[1] == NULL)
		exec_cleanup_exit(ctx, 0);
	if (_read_arg(argv[1], &code))
	{
		printf("minishell: exit: numeric argument required\n");
		exec_cleanup_exit(ctx, 2);
	}
	if (argv[2] == NULL)
		exec_cleanup_exit(ctx, code);
	dprintf(STDERR_FILENO, "minishell: exit: too many arguments\n");
	return (env_set_code(ctx->env_ctx, 1));
}

/* ************************************************************************** */
/*                                                                            */
/* Helper implementation                                                      */
/*                                                                            */
/* ************************************************************************** */

static bool	_read_arg(
				const char *str,
				int *_code
				)
{
	const char	*itr;
	long		code;
	int			sign;

	code = 0;
	sign = 1;
	while (ft_isspace(*str))
		++str;
	if (*str == '-' && ++str)
		sign = -1;
	else if (*str == '+')
		++str;
	itr = str;
	while (ft_isdigit(*itr))
	{
		code = 10 * code + *itr++ - '0';
		if (sign * code > INT_MAX || code * sign < INT_MIN)
			return (false);
	}
	while (ft_isspace(*itr))
		++itr;
	if (*itr != '\0')
		return (true);
	*_code = sign * (int)code;
	return (false);
}
