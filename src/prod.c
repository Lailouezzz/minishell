/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prod.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-boud <ale-boud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 02:53:20 by ale-boud          #+#    #+#             */
/*   Updated: 2023/12/10 19:44:03 by ale-boud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file prod.c
 * @author ale-boud (ale-boud@student.42.fr)
 * @brief The prod implementation.
 * @date 2023-11-29
 * @copyright Copyright (c) 2023
 */

// ************************************************************************** //
// *                                                                        * //
// * Includes.                                                              * //
// *                                                                        * //
// ************************************************************************** //

#include "ast.h"
#include "prod.h"

#include "utils.h"

// ************************************************************************** //
// *                                                                        * //
// * The production callbacks.                                              * //
// *                                                                        * //
// ************************************************************************** //

const t_lr_prod_cb	g_prod_cbs[PROD__COUNT] = {
[PROD_SIMPLE_COMMAND__RLPN] = {_prod_simple_command__rlpn, 2,
	_free_simple_command__rlpn},
[PROD_SIMPLE_COMMAND__1] = {_prod_simple_command__1, 1,
	_free_simple_command__1},
[PROD_SIMPLE_COMMAND__PNARL] = {_prod_simple_command__pnarl, 2,
	_free_simple_command__pnarl},
[PROD_SIMPLE_COMMAND__3] = {_prod_simple_command__3, 3,
	_free_simple_command__3},
[PROD_COMMAND_LINE] = {_prod_command_line, 1, _free_command_line},
[PROD_COMMAND__SS1] = {_prod_command__ss1, 1, _free_command__ss1},
[PROD_COMMAND__SS2] = {_prod_command__ss2, 2, _free_command__ss2},
[PROD_COMMAND__SC] = {_prod_command__sc, 1, _free_command__sc},
[PROD_SUBSHELL] = {_prod_subshell, 3, _free_subshell},
[PROD_AND_OR__1] = {_prod_and_or__1, 1, _free_and_or__1},
[PROD_AND_OR__3] = {_prod_and_or__3, 3, _free_and_or__3},
[PROD_PIPELINE__1] = {_prod_pipeline__1, 1, _free_pipeline__1},
[PROD_PIPELINE__3] = {_prod_pipeline__3, 3, _free_pipeline__3},
[PROD_IO_INFO] = {_prod_io_info, 2, _free_io_info},
[PROD_PROGNAME] = {_prod_progname, 1, _free_progname},
[PROD_ARG_RED__ARG] = {_prod_arg_red__arg, 1, _free_arg_red__arg},
[PROD_ARG_RED__IO] = {_prod_arg_red__io, 1, _free_arg_red__io},
[PROD_ARG_RED_LIST__1] = {_prod_arg_red_list__1, 1, _free_arg_red_list__1},
[PROD_ARG_RED_LIST__2] = {_prod_arg_red_list__2, 2, _free_arg_red_list__2},
[PROD_REDIRECT_LIST__1] = {_prod_redirect_list__1, 1, _free_redirect_list__1},
[PROD_REDIRECT_LIST__2] = {_prod_redirect_list__2, 2, _free_redirect_list__2},
};

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
	(void)(usrptr);
	(void)(item);
	return (NULL);
}

void	_free_simple_command__rlpn(
			void *to_free,
			void *usrptr
			)
{
	(void)(to_free);
	(void)(usrptr);
}

void	*_prod_simple_command__1(
			t_lr_stack_item *item,
			void *usrptr
			)
{
	(void)(usrptr);
	(void)(item);
	return (NULL);
}

void	_free_simple_command__1(
			void *to_free,
			void *usrptr
			)
{
	(void)(to_free);
	(void)(usrptr);
}

void	*_prod_simple_command__pnarl(
			t_lr_stack_item *item,
			void *usrptr
			)
{
	(void)(usrptr);
	(void)(item);
	return (NULL);
}

void	_free_simple_command__pnarl(
			void *to_free,
			void *usrptr
			)
{
	(void)(to_free);
	(void)(usrptr);
}

void	*_prod_simple_command__3(
			t_lr_stack_item *item,
			void *usrptr
			)
{
	(void)(usrptr);
	(void)(item);
	return (NULL);
}

void	_free_simple_command__3(
			void *to_free,
			void *usrptr
			)
{
	(void)(to_free);
	(void)(usrptr);
}

void	*_prod_command_line(
			t_lr_stack_item *item,
			void *usrptr
			)
{
	(void)(usrptr);
	(void)(item);
	return (NULL);
}

void	_free_command_line(
			void *to_free,
			void *usrptr
			)
{
	(void)(to_free);
	(void)(usrptr);
}

void	*_prod_command__ss1(
			t_lr_stack_item *item,
			void *usrptr
			)
{
	(void)(usrptr);
	(void)(item);
	return (NULL);
}

void	_free_command__ss1(
			void *to_free,
			void *usrptr
			)
{
	(void)(to_free);
	(void)(usrptr);
}

void	*_prod_command__ss2(
			t_lr_stack_item *item,
			void *usrptr
			)
{
	(void)(usrptr);
	(void)(item);
	return (NULL);
}

void	_free_command__ss2(
			void *to_free,
			void *usrptr
			)
{
	(void)(to_free);
	(void)(usrptr);
}

void	*_prod_command__sc(
			t_lr_stack_item *item,
			void *usrptr
			)
{
	(void)(usrptr);
	(void)(item);
	return (NULL);
}

void	_free_command__sc(
			void *to_free,
			void *usrptr
			)
{
	(void)(to_free);
	(void)(usrptr);
}

void	*_prod_subshell(
			t_lr_stack_item *item,
			void *usrptr
			)
{
	(void)(usrptr);
	(void)(item);
	return (NULL);
}

void	_free_subshell(
			void *to_free,
			void *usrptr
			)
{
	(void)(to_free);
	(void)(usrptr);
}

void	*_prod_and_or__1(
			t_lr_stack_item *item,
			void *usrptr
			)
{
	(void)(usrptr);
	(void)(item);
	return (NULL);
}

void	_free_and_or__1(
			void *to_free,
			void *usrptr
			)
{
	(void)(to_free);
	(void)(usrptr);
}

void	*_prod_and_or__3(
			t_lr_stack_item *item,
			void *usrptr
			)
{
	(void)(usrptr);
	(void)(item);
	return (NULL);
}

void	_free_and_or__3(
			void *to_free,
			void *usrptr
			)
{
	(void)(to_free);
	(void)(usrptr);
}

void	*_prod_pipeline__1(
			t_lr_stack_item *item,
			void *usrptr
			)
{
	(void)(usrptr);
	(void)(item);
	return (NULL);
}

void	_free_pipeline__1(
			void *to_free,
			void *usrptr
			)
{
	(void)(to_free);
	(void)(usrptr);
}

void	*_prod_pipeline__3(
			t_lr_stack_item *item,
			void *usrptr
			)
{
	(void)(usrptr);
	(void)(item);
	return (NULL);
}

void	_free_pipeline__3(
			void *to_free,
			void *usrptr
			)
{
	(void)(to_free);
	(void)(usrptr);
}

void	*_prod_io_info(
			t_lr_stack_item *item,
			void *usrptr
			)
{
	(void)(usrptr);
	(void)(item);
	return (NULL);
}

void	_free_io_info(
			void *to_free,
			void *usrptr
			)
{
	(void)(to_free);
	(void)(usrptr);
}

void	*_prod_progname(
			t_lr_stack_item *item,
			void *usrptr
			)
{
	(void)(usrptr);
	(void)(item);
	return (NULL);
}

void	_free_progname(
			void *to_free,
			void *usrptr
			)
{
	(void)(to_free);
	(void)(usrptr);
}

void	*_prod_arg_red__arg(
			t_lr_stack_item *item,
			void *usrptr
			)
{
	(void)(usrptr);
	(void)(item);
	return (NULL);
}

void	_free_arg_red__arg(
			void *to_free,
			void *usrptr
			)
{
	(void)(to_free);
	(void)(usrptr);
}

void	*_prod_arg_red__io(
			t_lr_stack_item *item,
			void *usrptr
			)
{
	(void)(usrptr);
	(void)(item);
	return (NULL);
}

void	_free_arg_red__io(
			void *to_free,
			void *usrptr
			)
{
	(void)(to_free);
	(void)(usrptr);
}

void	*_prod_arg_red_list__1(
			t_lr_stack_item *item,
			void *usrptr
			)
{
	(void)(usrptr);
	(void)(item);
	return (NULL);
}

void	_free_arg_red_list__1(
			void *to_free,
			void *usrptr
			)
{
	(void)(to_free);
	(void)(usrptr);
}

void	*_prod_arg_red_list__2(
			t_lr_stack_item *item,
			void *usrptr
			)
{
	(void)(usrptr);
	(void)(item);
	return (NULL);
}

void	_free_arg_red_list__2(
			void *to_free,
			void *usrptr
			)
{
	(void)(to_free);
	(void)(usrptr);
}

void	*_prod_redirect_list__1(
			t_lr_stack_item *item,
			void *usrptr
			)
{
	(void)(usrptr);
	(void)(item);
	return (NULL);
}

void	_free_redirect_list__1(
			void *to_free,
			void *usrptr
			)
{
	(void)(to_free);
	(void)(usrptr);
}

void	*_prod_redirect_list__2(
			t_lr_stack_item *item,
			void *usrptr
			)
{
	(void)(usrptr);
	(void)(item);
	return (NULL);
}

void	_free_redirect_list__2(
			void *to_free,
			void *usrptr
			)
{
	(void)(to_free);
	(void)(usrptr);
}
