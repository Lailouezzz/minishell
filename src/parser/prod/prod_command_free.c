/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prod_command_free.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-boud <ale-boud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 02:45:18 by ale-boud          #+#    #+#             */
/*   Updated: 2023/12/14 02:54:37 by ale-boud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file prod_command_free.c
 * @author ale-boud (ale-boud@student.42.fr)
 * @brief Prod callback for #s_command and #s_command_line.
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

void	_free_command_line(
			void *to_free,
			void *usrptr
			)
{
	(void)(usrptr);
	command_line_destroy(to_free);
}

void	_free_command__ss1(
			void *to_free,
			void *usrptr
			)
{
	(void)(usrptr);
	command_destroy(to_free);
}

void	_free_command__ss2(
			void *to_free,
			void *usrptr
			)
{
	(void)(usrptr);
	command_destroy(to_free);
}

void	_free_command__sc(
			void *to_free,
			void *usrptr
			)
{
	(void)(usrptr);
	command_destroy(to_free);
}
