/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dyn_str.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-boud <ale-boud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 17:05:37 by ale-boud          #+#    #+#             */
/*   Updated: 2024/01/22 05:11:00 by ale-boud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file dyn_str.c
 * @author ale-boud (ale-boud@student.42lehavre.fr)
 * @brief The implementation of a dynamic stirng.
 * @date 2023-12-10
 * @copyright Copyright (c) 2023
 */

// ************************************************************************** //
// *                                                                        * //
// * Includes.                                                              * //
// *                                                                        * //
// ************************************************************************** //

#include "utils.h"
#include "core/error_code.h"

#include "utils/dyn_str.h"

// ************************************************************************** //
// *                                                                        * //
// * Header function.                                                       * //
// *                                                                        * //
// ************************************************************************** //

t_ms_error	dyn_str_init(
				t_dyn_str *dstr
				)
{
	dstr->alloced = 1;
	dstr->len = 0;
	dstr->str = malloc(dstr->alloced + 1);
	if (dstr->str == NULL)
		return (MS_BAD_ALLOC);
	dstr->str[dstr->len] = '\0';
	return (MS_OK);
}

t_ms_error	dyn_str_pushback(
				t_dyn_str *dstr,
				char c
				)
{
	void	*tmp;
	int		r;

	if (dstr->str == NULL)
	{
		r = dyn_str_init(dstr);
		if (r != MS_OK)
			return (r);
	}
	if (dstr->len >= dstr->alloced)
	{
		tmp = dstr->str;
		dstr->str = ft_realloc(dstr->str, dstr->alloced + 1,
				dstr->alloced * 2 + 1);
		if (dstr->str == NULL)
		{
			free(tmp);
			return (MS_BAD_ALLOC);
		}
		dstr->alloced *= 2;
	}
	dstr->str[dstr->len++] = c;
	dstr->str[dstr->len] = '\0';
	return (MS_OK);
}

t_ms_error	dyn_str_cat(
				t_dyn_str *dstr,
				const char *str
				)
{
	void	*tmp;
	size_t	total_size;
	int		r;

	if (dstr->str == NULL)
	{
		r = dyn_str_init(dstr);
		if (r != MS_OK)
			return (r);
	}
	total_size = ft_strlen(str) + dstr->len;
	if (total_size >= dstr->alloced)
	{
		tmp = dstr->str;
		dstr->str = ft_realloc(dstr->str, dstr->alloced + 1,
				total_size + 1);
		if (dstr->str == NULL)
			return (free(tmp), MS_BAD_ALLOC);
		dstr->alloced = total_size;
	}
	ft_memcpy(dstr->str + dstr->len, str, ft_strlen(str) + 1);
	dstr->len = total_size;
	return (MS_OK);
}

void	dyn_str_destroy(
			t_dyn_str *dstr
			)
{
	if (dstr->str != NULL)
		free(dstr->str);
}
