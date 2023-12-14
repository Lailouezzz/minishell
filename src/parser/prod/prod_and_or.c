/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prod_and_or.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-boud <ale-boud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 02:45:18 by ale-boud          #+#    #+#             */
/*   Updated: 2023/12/14 02:54:53 by ale-boud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file prod_and_or.c
 * @author ale-boud (ale-boud@student.42.fr)
 * @brief Prod callback for #s_and_or.
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

void	*_prod_and_or__1(
			t_lr_stack_item *item,
			void *usrptr
			)
{
	t_pipeline *const	pl = item[0].data.derived.data;

	(void)(usrptr);
	return (and_or_leaf(pl));
}

void	_free_and_or__1(
			void *to_free,
			void *usrptr
			)
{
	(void)(usrptr);
	and_or_destroy(to_free);
}

void	*_prod_and_or__3(
			t_lr_stack_item *item,
			void *usrptr
			)
{
	t_and_or *const		left = item[0].data.derived.data;
	t_logic_type const	type = item[1].data.token.data.logic_type;
	t_pipeline *const	pl = item[2].data.derived.data;

	(void)(usrptr);
	return (and_or_node(left, type, pl));
}

void	_free_and_or__3(
			void *to_free,
			void *usrptr
			)
{
	(void)(usrptr);
	and_or_destroy(to_free);
}
