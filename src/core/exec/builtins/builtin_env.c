/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amassias <amassias@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 13:13:49 by amassias          #+#    #+#             */
/*   Updated: 2024/02/21 16:56:24 by amassias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file builtin_env.c
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
/* Header implementation                                                      */
/*                                                                            */
/* ************************************************************************** */

t_ms_error	builtin_env(
				t_exec_ctx *ctx,
				char **argv,
				char **envp
				)
{
	(void)argv;
	while (*envp)
		printf("%s\n", *envp++);
	return (env_set_code(ctx->env_ctx, 0));
}