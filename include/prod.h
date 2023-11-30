/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prod.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-boud <ale-boud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 01:40:36 by ale-boud          #+#    #+#             */
/*   Updated: 2023/11/29 14:19:36 by ale-boud         ###   ########.fr       */
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
	PROD_COMMAND__1,
	PROD_COMMAND__2,
	PROD_COMMAND_SIMPLE__1,
	PROD_COMMAND_SIMPLE__2,
	PROD_ARGS__1,
	PROD_ARGS__2,
	PROD_PROGNAME,
	PROD_COMMAND_IO__1,
	PROD_COMMAND_IO__2,
	PROD_IO_INFO,
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

void	*_prod_command__1_cb(
			t_lr_stack_item *item,
			void *usrptr
			);

void	_prod_command__1_free_cb(
			void *item,
			void *usrptr
			);

void	*_prod_command__2_cb(
			t_lr_stack_item *item,
			void *usrptr
			);

void	_prod_command__2_free_cb(
			void *item,
			void *usrptr
			);

void	*_prod_command_simple__1_cb(
			t_lr_stack_item *item,
			void *usrptr
			);

void	_prod_command_simple__1_free_cb(
			void *item,
			void *usrptr
			);

void	*_prod_command_simple__2_cb(
			t_lr_stack_item *item,
			void *usrptr
			);

void	_prod_command_simple__2_free_cb(
			void *item,
			void *usrptr
			);

void	*_prod_args__1_cb(
			t_lr_stack_item *item,
			void *usrptr
			);

void	_prod_args__1_free_cb(
			void *item,
			void *usrptr
			);

void	*_prod_args__2_cb(
			t_lr_stack_item *item,
			void *usrptr
			);

void	_prod_args__2_free_cb(
			void *item,
			void *usrptr
			);

void	*_prod_progname_cb(
			t_lr_stack_item *item,
			void *usrptr
			);

void	_prod_progname_free_cb(
			void *item,
			void *usrptr
			);

void	*_prod_command_io__1_cb(
			t_lr_stack_item *item,
			void *usrptr
			);

void	_prod_command_io__1_free_cb(
			void *item,
			void *usrptr
			);

void	*_prod_command_io__2_cb(
			t_lr_stack_item *item,
			void *usrptr
			);

void	_prod_command_io__2_free_cb(
			void *item,
			void *usrptr
			);

void	*_prod_io_info_cb(
			t_lr_stack_item *item,
			void *usrptr
			);

void	_prod_io_info_free_cb(
			void *item,
			void *usrptr
			);

#endif
