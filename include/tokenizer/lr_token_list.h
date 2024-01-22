/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lr_token_list.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-boud <ale-boud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 13:45:37 by ale-boud          #+#    #+#             */
/*   Updated: 2024/01/22 05:04:21 by ale-boud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file lr_token_list.h
 * @author ale-boud (ale-boud@student.42.fr)
 * @brief Definition of a lr_token dynamic list.
 * @date 2023-12-11
 * @copyright Copyright (c) 2023
 */

#ifndef LR_TOKEN_LIST_H
# define LR_TOKEN_LIST_H

// ************************************************************************** //
// *                                                                        * //
// * Includes.                                                              * //
// *                                                                        * //
// ************************************************************************** //

# include <stdlib.h>

# include <lr_token.h>

# include "core/error_code.h"

// ************************************************************************** //
// *                                                                        * //
// * Structure definition                                                   * //
// *                                                                        * //
// ************************************************************************** //

typedef struct s_lr_token_list
{
	t_lr_token	*lrtoks;

	size_t		alloced;

	size_t		used;
}	t_lr_token_list;

// ************************************************************************** //
// *                                                                        * //
// * Function definition.                                                   * //
// *                                                                        * //
// ************************************************************************** //

t_ms_error	lrtoks_init(
				t_lr_token_list *lrtoks
				);

t_ms_error	lrtoks_pushback(
				t_lr_token_list *lrtoks,
				const t_lr_token *lrtok
				);

void		lrtoks_destroy(
				t_lr_token_list *lrtoks
				);

t_lr_token	*lrtoks_end(
				t_lr_token_list *lrtoks
				);

size_t		lrtoks_size(
				t_lr_token_list *lrtoks
				);

#endif
