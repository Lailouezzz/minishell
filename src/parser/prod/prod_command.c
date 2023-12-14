/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prod_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-boud <ale-boud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 02:45:18 by ale-boud          #+#    #+#             */
/*   Updated: 2023/12/14 02:54:29 by ale-boud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file prod_command.c
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

void	*_prod_command_line(
			t_lr_stack_item *item,
			void *usrptr
			)
{
	t_and_or *const	and_or = item[0].data.derived.data;

	(void)(usrptr);
	return (command_line_create(and_or));
}

void	*_prod_command__ss1(
			t_lr_stack_item *item,
			void *usrptr
			)
{
	t_subshell *const	ss = item[0].data.derived.data;

	(void)(usrptr);
	return (command_create(ss, COMMAND_SUBSHELL));
}

void	*_prod_command__ss2(
			t_lr_stack_item *item,
			void *usrptr
			)
{
	t_subshell *const		ss = item[0].data.derived.data;
	t_redirect_list *const	rl = item[1].data.derived.data;

	(void)(usrptr);
	if (subshell_add_rl(ss, rl))
		return (NULL);
	return (command_create(ss, COMMAND_SUBSHELL));
}

void	*_prod_command__sc(
			t_lr_stack_item *item,
			void *usrptr
			)
{
	t_simple_command *const	sc = item[0].data.derived.data;

	(void)(usrptr);
	return (command_create(sc, COMMAND_SIMPLE_COMMAND));
}
