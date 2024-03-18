/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amassias <amassias@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 18:10:55 by amassias          #+#    #+#             */
/*   Updated: 2024/03/18 12:38:16 by amassias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file builtin_echo.c
 * @author Antoine Massias (amassias@student.42lehavre.fr)
 * @date 2024-02-15
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
/* Helper protoypes                                                           */
/*                                                                            */
/* ************************************************************************** */

bool	_parse_option(
			const char *arg,
			bool *nl
			)
{
	if (arg[0] != '-' || arg[1] == '\0')
		return (false);
	++arg;
	while (*arg)
	{
		if (*arg++ != 'n')
			return (false);
		*nl = true;
	}
	return (true);
}

/* ************************************************************************** */
/*                                                                            */
/* Header implementation                                                      */
/*                                                                            */
/* ************************************************************************** */

t_ms_error	builtin_echo(
				t_exec_ctx *ctx,
				char **argv,
				char **envp
				)
{
	bool	nl;

	(void)envp;
	++argv;
	nl = true;
	while (*argv)
	{
		if (!_parse_option(*argv, &nl))
			break ;
		++argv;
	}
	while (*argv)
	{
		dprintf(STDOUT_FILENO, "%s", *argv++);
		if (*argv)
			dprintf(STDOUT_FILENO, " ");
	}
	if (nl)
		dprintf(STDOUT_FILENO, "\n");
	return (env_set_code(ctx->env_ctx, 0));
}
