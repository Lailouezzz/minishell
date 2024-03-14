/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amassias <amassias@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 03:06:06 by ale-boud          #+#    #+#             */
/*   Updated: 2024/03/14 15:01:54 by amassias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file destroy.c
 * @author ale-boud (ale-boud@student.42.fr)
 * @brief Environnement destroy.
 * @date 2024-01-23
 * @copyright Copyright (c) 2024
 */

// ************************************************************************** //
// *                                                                        * //
// * Includes.                                                              * //
// *                                                                        * //
// ************************************************************************** //

#include "core/env.h"

#include <unistd.h>

// ************************************************************************** //
// *                                                                        * //
// * Header functions.                                                      * //
// *                                                                        * //
// ************************************************************************** //

void	env_ctx_heredocs_cleanup(
			t_env_ctx *env_ctx
			)
{
	size_t	count;

	if (env_ctx->heredocs.fds == NULL)
		return ;
	count = env_ctx->heredocs.count;
	if (env_ctx->heredocs._index < count)
		count = env_ctx->heredocs._index;
	while (count--)
		close(env_ctx->heredocs.fds[count]);
	free(env_ctx->heredocs.fds);
	env_ctx->heredocs.fds = NULL;
	env_ctx->heredocs.count = 0;
	env_ctx->heredocs._index = 0;
}

void	env_ctx_destroy(
			t_env_ctx *env_ctx
			)
{
	env_destroy(&env_ctx->env);
	free(env_ctx->current_code_str);
	env_ctx_heredocs_cleanup(env_ctx);
}

void	env_destroy(
			t_env *env
			)
{
	t_env_var	*envp;

	envp = env->env_vars;
	while (*envp != NULL)
	{
		free(*envp);
		++envp;
	}
	free(env->env_vars);
}
