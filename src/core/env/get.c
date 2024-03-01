/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-boud <ale-boud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 19:15:38 by ale-boud          #+#    #+#             */
/*   Updated: 2024/02/13 19:32:44 by ale-boud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file get.c
 * @author ale-boud (ale-boud@student.42.fr)
 * @brief Environment get function.
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

// ************************************************************************** //
// *                                                                        * //
// * Header function.                                                       * //
// *                                                                        * //
// ************************************************************************** //

const char	*env_ctx_get_variable(
				t_env_ctx *env_ctx,
				const char *name
				)
{
	t_env_var *const	exist = _env_exist(&env_ctx->env, name);

	if (exist == NULL)
		return (NULL);
	return ((*exist) + ft_strlen(name) + 1);
}
