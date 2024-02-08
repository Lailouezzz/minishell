/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-boud <ale-boud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 01:08:41 by ale-boud          #+#    #+#             */
/*   Updated: 2024/02/08 16:44:41 by ale-boud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file env.h
 * @author ale-boud (ale-boud@student.42.fr)
 * @brief Definition of the environment of the shell.
 * @date 2023-12-12
 * @copyright Copyright (c) 2023
 */

#ifndef ENV_H
# define ENV_H

// ************************************************************************** //
// *                                                                        * //
// * Includes.                                                              * //
// *                                                                        * //
// ************************************************************************** //

# include <stdlib.h>

# include "core/status_code.h"
# include "core/error_code.h"

// ************************************************************************** //
// *                                                                        * //
// * Current signo global var.                                              * //
// *                                                                        * //
// ************************************************************************** //

extern volatile int	g_signo;

// ************************************************************************** //
// *                                                                        * //
// * Structure definition.                                                  * //
// *                                                                        * //
// ************************************************************************** //

# define MS_PROMPT "Bite> "

typedef char *		t_env_var;

typedef struct s_env
{
	t_env_var	*env_vars;
	size_t		alloced;
	size_t		used;
}					t_env;

typedef struct s_env_ctx
{
	char		*pn;
	t_env		env;
	int			current_code;
}					t_env_ctx;

// ************************************************************************** //
// *                                                                        * //
// * Function definition.                                                   * //
// *                                                                        * //
// ************************************************************************** //

t_ms_error	env_ctx_init(
				t_env_ctx *env_ctx,
				char *pn,
				char **envp
				);

const char	*env_ctx_get_variable(
				t_env_ctx *env_ctx,
				char *var_name
				);

t_ms_error	env_init(
				t_env *env,
				char **envp
				);

t_ms_error	env_set_var(
				t_env *env,
				t_env_var var
				);

t_ms_error	env_unset_var(
				t_env *env,
				t_env_var var
				);

#endif
