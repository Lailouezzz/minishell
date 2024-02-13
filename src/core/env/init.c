/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-boud <ale-boud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 03:06:06 by ale-boud          #+#    #+#             */
/*   Updated: 2024/02/13 19:22:44 by ale-boud         ###   ########.fr       */
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

static t_ms_error	_env_init_fill(
						t_env *env,
						char **envp
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
	printf("PATH : %s\n", env_ctx_get_variable(env_ctx, "PATH"));
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
	r = _env_init_fill(env, envp);
	if (r != MS_OK)
		return (env_destroy(env), r);
	t_env_var	*e;
	e = env->env_vars;
	while (*e != NULL)
	{
		printf("var : \"%s\"\n", *e);
		++e;
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
	env->env_vars = malloc(1 * sizeof(*env->env_vars));
	if (env->env_vars == NULL)
		return (MS_BAD_ALLOC);
	env->env_vars[0] = NULL;
	env->used = 0;
	env->alloced = 1;
	return (MS_OK);
}

static t_ms_error	_env_init_fill(
						t_env *env,
						char **envp
						)
{
	char		*varname;
	char		*varvalue;
	t_ms_error	r;

	while (*envp != NULL)
	{
		varname = _env_take_varname(*envp);
		varvalue = _env_take_varvalue(*envp);
		if (varname == NULL)
			return (free(varvalue), MS_BAD_ALLOC);
		if (varvalue == NULL)
			return (free(varname), MS_BAD_ALLOC);
		r = env_set_var(env, varname, varvalue);
		if (r != MS_OK)
			return (free(varname), free(varvalue), r);
		++envp;
	}
	return (MS_OK);
}
