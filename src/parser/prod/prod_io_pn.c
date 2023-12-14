/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prod_io_pn.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-boud <ale-boud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 02:45:18 by ale-boud          #+#    #+#             */
/*   Updated: 2023/12/14 02:55:17 by ale-boud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file prod_io_pn.c
 * @author ale-boud (ale-boud@student.42.fr)
 * @brief Prod callback for #s_io_info and #t_progname.
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

void	*_prod_io_info(
			t_lr_stack_item *item,
			void *usrptr
			)
{
	t_io_type const	type = item[0].data.token.data.io_type;
	char *const		file = item[1].data.token.data.word;

	(void)(usrptr);
	return (io_info_create(type, file));
}

void	_free_io_info(
			void *to_free,
			void *usrptr
			)
{
	(void)(usrptr);
	io_info_destroy(to_free);
}

void	*_prod_progname(
			t_lr_stack_item *item,
			void *usrptr
			)
{
	char *const	word = item[0].data.token.data.word;

	(void)(usrptr);
	return ((t_progname)word);
}

void	_free_progname(
			void *to_free,
			void *usrptr
			)
{
	(void)(usrptr);
	free(to_free);
}
