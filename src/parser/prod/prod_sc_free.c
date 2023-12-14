/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prod_sc_free.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-boud <ale-boud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 02:45:18 by ale-boud          #+#    #+#             */
/*   Updated: 2023/12/14 02:51:28 by ale-boud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file prod_sc_free.c
 * @author ale-boud (ale-boud@student.42.fr)
 * @brief Prod callback for simple_command.
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

void	_free_simple_command__rlpn(
			void *to_free,
			void *usrptr
			)
{
	(void)(usrptr);
	simple_command_destroy(to_free);
}

void	_free_simple_command__1(
			void *to_free,
			void *usrptr
			)
{
	(void)(usrptr);
	simple_command_destroy(to_free);
}

void	_free_simple_command__pnarl(
			void *to_free,
			void *usrptr
			)
{
	(void)(usrptr);
	simple_command_destroy(to_free);
}

void	_free_simple_command__3(
			void *to_free,
			void *usrptr
			)
{
	(void)(usrptr);
	simple_command_destroy(to_free);
}
