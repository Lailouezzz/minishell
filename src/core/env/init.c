/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-boud <ale-boud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 03:06:06 by ale-boud          #+#    #+#             */
/*   Updated: 2024/03/12 16:43:11 by ale-boud         ###   ########.fr       */
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

#include <libft.h>

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
	env_ctx->current_code = MS_STATUS_OK;
	env_ctx->current_code_str = ft_itoa(MS_STATUS_OK);
	if (env_ctx->current_code_str == NULL)
		return (env_ctx_destroy(env_ctx), MS_BAD_ALLOC);
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
	char *const	pwd = getcwd(NULL, 0);
	int			r;

	if (pwd == NULL)
		return (MS_BAD_ALLOC);
	env->env_vars = malloc(2 * sizeof(*env->env_vars));
	if (env->env_vars == NULL)
		return (MS_BAD_ALLOC);
	env->env_vars[0] = NULL;
	env->used = 0;
	env->alloced = 1;
	r = env_set_var(env, "PWD", pwd);
	free(pwd);
	return (r);
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
		free(varname);
		free(varvalue);
		if (r != MS_OK)
			return (r);
		++envp;
	}
	return (MS_OK);
}
