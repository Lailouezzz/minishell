/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-boud <ale-boud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 01:08:41 by ale-boud          #+#    #+#             */
/*   Updated: 2024/01/22 22:04:55 by ale-boud         ###   ########.fr       */
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

// ************************************************************************** //
// *                                                                        * //
// * Structure definition.                                                  * //
// *                                                                        * //
// ************************************************************************** //

# define MS_PROMPT "Bite> "

typedef char *	t_env_var;

typedef struct s_env
{
	t_env_var	*env_vars;
	size_t		alloced;
	size_t		used;
}	t_env;

typedef struct s_env_ctx
{
	char		*pn;
	t_ms_status	current_code;
	t_env		env;
}	t_env_ctx;

// ************************************************************************** //
// *                                                                        * //
// * Function definition.                                                   * //
// *                                                                        * //
// ************************************************************************** //

int		env_ctx_init(
			t_env_ctx *env_ctx,
			char *pn,
			char **env
			);

char	*env_ctx_get_variable(
			t_env_ctx *env_ctx,
			char *var_name
			);

int		env_init(
			t_env *env,
			char **envp
			);

int		env_add_var(
			t_env *env,
			t_env_var var
			);

int		env_unset_var(
			t_env *env,
			t_env_var var
			);

#endif
