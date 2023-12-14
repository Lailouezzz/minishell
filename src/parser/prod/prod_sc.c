/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prod_sc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-boud <ale-boud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 02:45:18 by ale-boud          #+#    #+#             */
/*   Updated: 2023/12/14 02:51:10 by ale-boud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file prod_sc.c
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

void	*_prod_simple_command__rlpn(
			t_lr_stack_item *item,
			void *usrptr
			)
{
	t_redirect_list *const	rl = item[0].data.derived.data;
	t_progname const		pn = item[1].data.derived.data;
	t_simple_command		*sc;

	(void)(usrptr);
	sc = simple_command_create(pn);
	if (sc == NULL)
		return (redirect_list_destroy(rl), NULL);
	if (simple_command_add_rl(sc, rl))
		return (NULL);
	return (sc);
}

void	*_prod_simple_command__1(
			t_lr_stack_item *item,
			void *usrptr
			)
{
	t_progname const	pn = item[0].data.derived.data;

	(void)(usrptr);
	return (simple_command_create(pn));
}

void	*_prod_simple_command__pnarl(
			t_lr_stack_item *item,
			void *usrptr
			)
{
	t_progname const			pn = item[0].data.derived.data;
	t_args_redirect_list *const	arl = item[1].data.derived.data;
	t_simple_command			*sc;

	(void)(usrptr);
	sc = simple_command_create(pn);
	if (sc == NULL)
		return (args_redirect_list_destroy(arl), NULL);
	if (simple_command_add_arl(sc, arl))
		return (NULL);
	return (sc);
}

void	*_prod_simple_command__3(
			t_lr_stack_item *item,
			void *usrptr
			)
{
	t_redirect_list *const		rl = item[0].data.derived.data;
	t_progname const			pn = item[1].data.derived.data;
	t_args_redirect_list *const	arl = item[2].data.derived.data;
	t_simple_command			*sc;

	(void)(usrptr);
	sc = simple_command_create(pn);
	if (sc == NULL)
		return (args_redirect_list_destroy(arl),
			redirect_list_destroy(rl), NULL);
	if (simple_command_add_rl(sc, rl))
		return (args_redirect_list_destroy(arl), NULL);
	if (simple_command_add_arl(sc, arl))
		return (NULL);
	return (sc);
}
