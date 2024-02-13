/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-boud <ale-boud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 03:06:06 by ale-boud          #+#    #+#             */
/*   Updated: 2024/02/13 17:49:01 by ale-boud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file init.c
 * @author ale-boud (ale-boud@student.42.fr)
 * @brief Environnement init.
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
// * Helper function definition.                                            * //
// *                                                                        * //
// ************************************************************************** //

static t_ms_error	_env_init(
						t_env *env
						);

// ************************************************************************** //
// *                                                                        * //
// * Header functions.                                                      * //
// *                                                                        * //
// ************************************************************************** //

t_ms_error	env_ctx_init(
				t_env_ctx *env_ctx,
				char *pn,
				char **envp
				)
{
	t_ms_error	r;

	env_ctx->pn = pn;
	r = env_init(&env_ctx->env, envp);
	if (r != MS_OK)
		return (r);
	env_ctx->current_code = MS_STATUS_OK;
	return (MS_OK);
}

t_ms_error	env_init(
				t_env *env,
				char **envp
				)
{
	t_ms_error	r;

	r = _env_init(env);
	if (r != MS_OK)
		return (r);
	while (*envp != NULL)
	{
		++envp;
	}
	return (MS_OK);
}

// ************************************************************************** //
// *                                                                        * //
// * Helper functions.                                                      * //
// *                                                                        * //
// ************************************************************************** //

t_ms_error	_env_init(
				t_env *env
				)
{
	return (MS_OK);
}
