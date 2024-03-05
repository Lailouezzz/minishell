/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amassias <amassias@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 18:10:55 by amassias          #+#    #+#             */
/*   Updated: 2024/03/01 00:54:36 by amassias         ###   ########.fr       */
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
	if (argv[0] != NULL && ft_strcmp(argv[0], "-n") == 0)
	{
		nl = false;
		++argv;
	}
	while (*argv)
	{
		printf("%s", *argv++);
		if (*argv)
			printf(" ");
	}
	if (nl)
		printf("\n");
	return (env_set_code(ctx->env_ctx, 0));
}