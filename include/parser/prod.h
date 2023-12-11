/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prod.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-boud <ale-boud@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 01:40:36 by ale-boud          #+#    #+#             */
/*   Updated: 2023/12/10 14:07:07 by ale-boud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file prod.h
 * @author ale-boud (ale-boud@student.42.fr)
 * @brief The LR rule definition. 
 * @date 2023-11-29
 * @copyright Copyright (c) 2023
 */

#ifndef PROD_H
# define PROD_H

// ************************************************************************** //
// *                                                                        * //
// * Includes.                                                              * //
// *                                                                        * //
// ************************************************************************** //

# include <lr_parser.h>

// ************************************************************************** //
// *                                                                        * //
// * Structure definition.                                                  * //
// *                                                                        * //
// ************************************************************************** //

typedef enum e_prod_id {
	PROD_SIMPLE_COMMAND__1,
	PROD_SIMPLE_COMMAND__RLPN,
	PROD_SIMPLE_COMMAND__PNARL,
	PROD_SIMPLE_COMMAND__3,
	PROD_COMMAND_LINE,
	PROD_COMMAND__SS1,
	PROD_COMMAND__SS2,
	PROD_COMMAND__SC,
	PROD_SUBSHELL,
	PROD_AND_OR__1,
	PROD_AND_OR__3,
	PROD_PIPELINE__1,
	PROD_PIPELINE__3,
	PROD_IO_INFO,
	PROD_PROGNAME,
	PROD_ARG_RED__ARG,
	PROD_ARG_RED__IO,
	PROD_ARG_RED_LIST__1,
	PROD_ARG_RED_LIST__2,
	PROD_REDIRECT_LIST__1,
	PROD_REDIRECT_LIST__2,
	PROD__COUNT,
}	t_prod_id;

// ************************************************************************** //
// *                                                                        * //
// * Production callbacks table definition.                                 * //
// *                                                                        * //
// ************************************************************************** //

extern const t_lr_prod_cb	g_prod_cbs[PROD__COUNT];

// ************************************************************************** //
// *                                                                        * //
// * Production callbacks.                                                  * //
// *                                                                        * //
// ************************************************************************** //

void	*_prod_simple_command__rlpn(
			t_lr_stack_item *item,
			void *usrptr
			);

void	_free_simple_command__rlpn(
			void *to_free,
			void *usrptr
			);

void	*_prod_simple_command__1(
			t_lr_stack_item *item,
			void *usrptr
			);

void	_free_simple_command__1(
			void *to_free,
			void *usrptr
			);

void	*_prod_simple_command__pnarl(
			t_lr_stack_item *item,
			void *usrptr
			);

void	_free_simple_command__pnarl(
			void *to_free,
			void *usrptr
			);

void	*_prod_simple_command__3(
			t_lr_stack_item *item,
			void *usrptr
			);

void	_free_simple_command__3(
			void *to_free,
			void *usrptr
			);

void	*_prod_command_line(
			t_lr_stack_item *item,
			void *usrptr
			);

void	_free_command_line(
			void *to_free,
			void *usrptr
			);

void	*_prod_command__ss1(
			t_lr_stack_item *item,
			void *usrptr
			);

void	_free_command__ss1(
			void *to_free,
			void *usrptr
			);

void	*_prod_command__ss2(
			t_lr_stack_item *item,
			void *usrptr
			);

void	_free_command__ss2(
			void *to_free,
			void *usrptr
			);

void	*_prod_command__sc(
			t_lr_stack_item *item,
			void *usrptr
			);

void	_free_command__sc(
			void *to_free,
			void *usrptr
			);

void	*_prod_subshell(
			t_lr_stack_item *item,
			void *usrptr
			);

void	_free_subshell(
			void *to_free,
			void *usrptr
			);

void	*_prod_and_or__1(
			t_lr_stack_item *item,
			void *usrptr
			);

void	_free_and_or__1(
			void *to_free,
			void *usrptr
			);

void	*_prod_and_or__3(
			t_lr_stack_item *item,
			void *usrptr
			);

void	_free_and_or__3(
			void *to_free,
			void *usrptr
			);

void	*_prod_pipeline__1(
			t_lr_stack_item *item,
			void *usrptr
			);

void	_free_pipeline__1(
			void *to_free,
			void *usrptr
			);

void	*_prod_pipeline__3(
			t_lr_stack_item *item,
			void *usrptr
			);

void	_free_pipeline__3(
			void *to_free,
			void *usrptr
			);

void	*_prod_io_info(
			t_lr_stack_item *item,
			void *usrptr
			);

void	_free_io_info(
			void *to_free,
			void *usrptr
			);

void	*_prod_progname(
			t_lr_stack_item *item,
			void *usrptr
			);

void	_free_progname(
			void *to_free,
			void *usrptr
			);

void	*_prod_arg_red__arg(
			t_lr_stack_item *item,
			void *usrptr
			);

void	_free_arg_red__arg(
			void *to_free,
			void *usrptr
			);

void	*_prod_arg_red__io(
			t_lr_stack_item *item,
			void *usrptr
			);

void	_free_arg_red__io(
			void *to_free,
			void *usrptr
			);

void	*_prod_arg_red_list__1(
			t_lr_stack_item *item,
			void *usrptr
			);

void	_free_arg_red_list__1(
			void *to_free,
			void *usrptr
			);

void	*_prod_arg_red_list__2(
			t_lr_stack_item *item,
			void *usrptr
			);

void	_free_arg_red_list__2(
			void *to_free,
			void *usrptr
			);

void	*_prod_redirect_list__1(
			t_lr_stack_item *item,
			void *usrptr
			);

void	_free_redirect_list__1(
			void *to_free,
			void *usrptr
			);

void	*_prod_redirect_list__2(
			t_lr_stack_item *item,
			void *usrptr
			);

void	_free_redirect_list__2(
			void *to_free,
			void *usrptr
			);

#endif
