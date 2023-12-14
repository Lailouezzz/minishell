/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prod_subshell.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-boud <ale-boud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 02:45:18 by ale-boud          #+#    #+#             */
/*   Updated: 2023/12/14 02:54:20 by ale-boud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file prod_subshell.c
 * @author ale-boud (ale-boud@student.42.fr)
 * @brief Prod callback for #s_subshell.
 * @date 2023-12-14
 * @copyright Copyright (c) 2023
 */

// ************************************************************************** //
// *                                                                        * //
// * Includes.                                                              * //
// *                                                                        * //
// ************************************************************************** //

#include "parser/ast.h"
#include "parser/prod.h"

#include "utils.h"

// ************************************************************************** //
// *                                                                        * //
// * Callback functions.                                                    * //
// *                                                                        * //
// ************************************************************************** //

void	*_prod_subshell(
			t_lr_stack_item *item,
			void *usrptr
			)
{
	t_and_or *const	and_or = item[1].data.derived.data;

	(void)(usrptr);
	return (subshell_create(and_or));
}

void	_free_subshell(
			void *to_free,
			void *usrptr
			)
{
	(void)(usrptr);
	subshell_destroy(to_free);
}
