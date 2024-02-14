/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-boud <ale-boud@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 18:39:25 by ale-boud          #+#    #+#             */
/*   Updated: 2024/02/14 16:36:13 by ale-boud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file set.c
 * @author ale-boud (ale-boud@student.42.fr)
 * @brief Environment set function.
 * @date 2024-02-13
 * @copyright Copyright (c) 2024
 */

// ************************************************************************** //
// *                                                                        * //
// * Includes.                                                              * //
// *                                                                        * //
// ************************************************************************** //

#include <libft.h>

#include "core/env.h"

#include "utils.h"

// ************************************************************************** //
// *                                                                        * //
// * Helper function declaration.                                           * //
// *                                                                        * //
// ************************************************************************** //

static t_ms_error	_env_pushback_var(
						t_env *env,
						t_env_var var
						);

// ************************************************************************** //
// *                                                                        * //
// * Function header.                                                       * //
// *                                                                        * //
// ************************************************************************** //

t_ms_error	env_set_var(
				t_env *env,
				const char *name,
				const char *value
				)
{
	t_env_var *const	exist = _env_exist(env, name);
	t_env_var			var;
	t_ms_error			r;

	var = _env_format_var(name, value);
	if (var == NULL)
		return (MS_BAD_ALLOC);
	if (exist != NULL)
	{
		free(*exist);
		*exist = var;
	}
	else
	{
		r = _env_pushback_var(env, var);
		if (r != MS_OK)
			return (free(var), r);
	}
	return (MS_OK);
}

t_ms_error	env_set_code(
				t_env_ctx *env_ctx,
				t_ms_status code
				)
{
	env_ctx->current_code = code;
	free(env_ctx->current_code_str);
	env_ctx->current_code_str = ft_itoa(code);
	if (env_ctx->current_code_str == NULL)
		return (env_ctx_destroy(env_ctx), MS_BAD_ALLOC);
	return (MS_OK);
}

t_ms_error	env_unset_var(
				t_env *env,
				const char *name
				)
{
	
}

// ************************************************************************** //
// *                                                                        * //
// * Helper function.                                                       * //
// *                                                                        * //
// ************************************************************************** //

static t_ms_error	_env_pushback_var(
						t_env *env,
						t_env_var var
						)
{
	if (env->used >= env->alloced)
	{
		env->env_vars = _realloc(env->env_vars,
				(env->alloced + 1) * sizeof(*env->env_vars),
				((env->alloced * 2) + 1) * sizeof(*env->env_vars));
		env->alloced *= 2;
		if (env->env_vars == NULL)
			return (MS_BAD_ALLOC);
	}
	env->env_vars[env->used++] = var;
	env->env_vars[env->used] = NULL;
	return (MS_OK);
}
