/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-boud <ale-boud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 01:08:41 by ale-boud          #+#    #+#             */
/*   Updated: 2024/03/11 17:34:37 by ale-boud         ###   ########.fr       */
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

# define MS_PROMPT "\e[31;42mminishell\e[m> "

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
	char		*current_code_str;
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

void		env_ctx_destroy(
				t_env_ctx *env_ctx
				);

void		env_destroy(
				t_env *env
				);

const char	*env_ctx_get_variable(
				t_env_ctx *env_ctx,
				const char *name
				);

t_ms_error	env_init(
				t_env *env,
				char **envp
				);

t_ms_error	env_set_var(
				t_env *env,
				const char *name,
				const char *value
				);

t_ms_error	env_set_code(
				t_env_ctx *env_ctx,
				t_ms_status code
				);

t_ms_error	env_unset_var(
				t_env *env,
				const char *name
				);

// ************************************************************************** //
// *                                                                        * //
// * Global helper definition.                                              * //
// *                                                                        * //
// ************************************************************************** //

char		*_env_take_varname(
				const t_env_var env_var
				);

char		*_env_take_varvalue(
				const t_env_var env_var
				);

t_env_var	*_env_exist(
				t_env *env,
				const char *name
				);

t_env_var	_env_format_var(
				const char *name,
				const char *value
				);

#endif
