/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prod_rl.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-boud <ale-boud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 02:45:18 by ale-boud          #+#    #+#             */
/*   Updated: 2023/12/14 02:56:20 by ale-boud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file prod_rl.c
 * @author ale-boud (ale-boud@student.42.fr)
 * @brief Prod callback for #s_redirect_list.
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

void	*_prod_redirect_list__1(
			t_lr_stack_item *item,
			void *usrptr
			)
{
	t_io_info *const	io_info = item[0].data.derived.data;

	(void)(usrptr);
	return (redirect_list_create(io_info));
}

void	_free_redirect_list__1(
			void *to_free,
			void *usrptr
			)
{
	(void)(usrptr);
	redirect_list_destroy(to_free);
}

void	*_prod_redirect_list__2(
			t_lr_stack_item *item,
			void *usrptr
			)
{
	t_redirect_list *const	rl = item[0].data.derived.data;
	t_io_info *const		io_info = item[1].data.derived.data;

	(void)(usrptr);
	if (redirect_list_pushback(rl, io_info))
		return (NULL);
	return (rl);
}

void	_free_redirect_list__2(
			void *to_free,
			void *usrptr
			)
{
	(void)(usrptr);
	redirect_list_destroy(to_free);
}
