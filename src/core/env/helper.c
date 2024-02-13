/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-boud <ale-boud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 17:01:31 by ale-boud          #+#    #+#             */
/*   Updated: 2024/02/13 21:42:42 by ale-boud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file helper.c
 * @author ale-boud (ale-boud@student.42.fr)
 * @brief Environment helper functions.
 * @date 2024-02-13
 * @copyright Copyright (c) 2024
 */

// ************************************************************************** //
// *                                                                        * //
// * Includes.                                                              * //
// *                                                                        * //
// ************************************************************************** //

#include "core/env.h"
#include "utils.h"
#include <libft.h>

// ************************************************************************** //
// *                                                                        * //
// * Header functions.                                                      * //
// *                                                                        * //
// ************************************************************************** //

static int	__env_take_limiter(
				char c
				)
{
	return (c != '=');
}

char	*_env_take_varname(
			const t_env_var env_var
			)
{
	const int	len = ft_count_if(env_var, __env_take_limiter);
	char		*s;

	s = malloc(len + 1);
	if (s == NULL)
		return (NULL);
	ft_memcpy(s, env_var, len);
	s[len] = '\0';
	return (s);
}

char	*_env_take_varvalue(
			const t_env_var env_var
			)
{
	const t_env_var	value = ft_strchr(env_var, '=');

	if (value == NULL)
		return (NULL);
	return (ft_strdup(value + 1));
}

t_env_var	*_env_exist(
				t_env *env,
				const char *name
				)
{
	t_env_var	*envp;
	const int	namelen = ft_strlen(name);

	envp = env->env_vars;
	while (*envp != NULL)
	{
		if (ft_strncmp(*envp, name, namelen) == 0
			&& ft_strlen(*envp) >= namelen + 1
			&& (*envp)[namelen] == '=')
			return (envp);
		++envp;
	}
	return (NULL);
}

t_env_var	_env_format_var(
				const char *name,
				const char *value
				)
{
	t_env_var	var;
	const int	namelen = ft_strlen(name);
	const int	valuelen = ft_strlen(value);

	var = malloc(namelen + valuelen + 2);
	if (var == NULL)
		return (NULL);
	ft_memcpy(var, name, namelen);
	var[namelen] = '=';
	ft_memcpy(var + namelen + 1, value, valuelen);
	var[namelen + valuelen + 1] = '\0';
	return (var);
}
