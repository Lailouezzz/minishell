/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-boud <ale-boud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 03:06:06 by ale-boud          #+#    #+#             */
/*   Updated: 2024/02/13 21:35:30 by ale-boud         ###   ########.fr       */
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

// ************************************************************************** //
// *                                                                        * //
// * Header functions.                                                      * //
// *                                                                        * //
// ************************************************************************** //

void	env_ctx_destroy(
			t_env_ctx *env_ctx
			)
{
	env_destroy(&env_ctx->env);
	free(env_ctx->current_code_str);
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
