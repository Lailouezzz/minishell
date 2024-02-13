/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-boud <ale-boud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 17:01:31 by ale-boud          #+#    #+#             */
/*   Updated: 2024/02/13 17:23:46 by ale-boud         ###   ########.fr       */
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
