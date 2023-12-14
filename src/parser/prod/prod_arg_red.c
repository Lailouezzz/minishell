/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prod_arg_red.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-boud <ale-boud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 02:45:18 by ale-boud          #+#    #+#             */
/*   Updated: 2023/12/14 02:55:40 by ale-boud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file prod_arg_red.c
 * @author ale-boud (ale-boud@student.42.fr)
 * @brief Prod callback for #s_arg_red.
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

void	*_prod_arg_red__arg(
			t_lr_stack_item *item,
			void *usrptr
			)
{
	char *const	arg = item[0].data.token.data.word;

	(void)(usrptr);
	return (arg_red_create_arg(arg));
}

void	_free_arg_red__arg(
			void *to_free,
			void *usrptr
			)
{
	(void)(usrptr);
	arg_red_destroy(to_free);
}

void	*_prod_arg_red__io(
			t_lr_stack_item *item,
			void *usrptr
			)
{
	t_io_info *const	io_info = item[0].data.derived.data;

	(void)(usrptr);
	return (arg_red_create_redirect(io_info));
}

void	_free_arg_red__io(
			void *to_free,
			void *usrptr
			)
{
	(void)(usrptr);
	arg_red_destroy(to_free);
}
