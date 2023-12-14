/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prod_arl.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-boud <ale-boud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 02:45:18 by ale-boud          #+#    #+#             */
/*   Updated: 2023/12/14 02:56:06 by ale-boud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file prod_arl.c
 * @author ale-boud (ale-boud@student.42.fr)
 * @brief Prod callback for #s_arg_redirect_list.
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

void	*_prod_arg_red_list__1(
			t_lr_stack_item *item,
			void *usrptr
			)
{
	t_arg_red *const	ar = item[0].data.derived.data;

	(void)(usrptr);
	return (args_redirect_list_create(ar));
}

void	_free_arg_red_list__1(
			void *to_free,
			void *usrptr
			)
{
	(void)(usrptr);
	args_redirect_list_destroy(to_free);
}

void	*_prod_arg_red_list__2(
			t_lr_stack_item *item,
			void *usrptr
			)
{
	t_args_redirect_list *const	arl = item[0].data.derived.data;
	t_arg_red *const			ar = item[1].data.derived.data;

	(void)(usrptr);
	if (args_redirect_list_pusback(arl, ar))
		return (NULL);
	return (arl);
}

void	_free_arg_red_list__2(
			void *to_free,
			void *usrptr
			)
{
	(void)(usrptr);
	args_redirect_list_destroy(to_free);
}
