/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dyn_str.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-boud <ale-boud@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 16:59:07 by ale-boud          #+#    #+#             */
/*   Updated: 2023/12/10 17:05:11 by ale-boud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file dyn_str.h
 * @author ale-boud (ale-boud@student.42lehavre.fr)
 * @brief The definition of a dynamic string.
 * @date 2023-12-10
 * @copyright Copyright (c) 2023
 */

#ifndef DYN_STR_H
# define DYN_STR_H

// ************************************************************************** //
// *                                                                        * //
// * Includes.                                                              * //
// *                                                                        * //
// ************************************************************************** //

# include <stdlib.h>

// ************************************************************************** //
// *                                                                        * //
// * Structure definition.                                                  * //
// *                                                                        * //
// ************************************************************************** //

typedef struct s_dyn_str
{
	char	*str;
	size_t	len;
	size_t	alloced;
}	t_dyn_str;

// ************************************************************************** //
// *                                                                        * //
// * Function definition.                                                   * //
// *                                                                        * //
// ************************************************************************** //

int		dyn_str_init(
			t_dyn_str *dstr
			);

int		dyn_str_pushback(
			t_dyn_str *dstr,
			char c
			);

int		dyn_str_cat(
			t_dyn_str *dstr,
			const char *str
			);

void	dyn_str_destroy(
			t_dyn_str *dstr
			);

#endif
