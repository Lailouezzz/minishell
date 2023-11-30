/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prod.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-boud <ale-boud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 02:53:20 by ale-boud          #+#    #+#             */
/*   Updated: 2023/11/29 14:23:35 by ale-boud         ###   ########.fr       */
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
[PROD_COMMAND__1] = {_prod_command__1_cb, 1, _prod_command__1_free_cb},
[PROD_COMMAND__2] = {_prod_command__2_cb, 2, _prod_command__2_free_cb},
[PROD_COMMAND_SIMPLE__1] = {_prod_command_simple__1_cb, 1,
	_prod_command_simple__1_free_cb},
[PROD_COMMAND_SIMPLE__2] = {_prod_command_simple__2_cb, 2,
	_prod_command_simple__2_free_cb},
[PROD_ARGS__1] = {_prod_args__1_cb, 1, _prod_args__1_free_cb},
[PROD_ARGS__2] = {_prod_args__2_cb, 2, _prod_args__2_free_cb},
[PROD_PROGNAME] = {_prod_progname_cb, 1, _prod_progname_free_cb},
[PROD_COMMAND_IO__1] = {_prod_command_io__1_cb, 1, _prod_command_io__1_free_cb},
[PROD_COMMAND_IO__2] = {_prod_command_io__2_cb, 2, _prod_command_io__2_free_cb},
[PROD_IO_INFO] = {_prod_io_info_cb, 2, _prod_io_info_free_cb},
};

// ************************************************************************** //
// *                                                                        * //
// * Callback functions.                                                    * //
// *                                                                        * //
// ************************************************************************** //

void	*_prod_command__1_cb(
			t_lr_stack_item *item,
			void *usrptr
			)
{
	return (item[0].data.derived.data);
}

void	_prod_command__1_free_cb(
			void *to_free,
			void *usrptr
			)
{
	command_destroy(to_free);
}

void	*_prod_command__2_cb(
			t_lr_stack_item *item,
			void *usrptr
			)
{
	if (command_add_io(item[0].data.derived.data, item[1].data.derived.data))
		return (NULL);
	return (item[0].data.derived.data);
}

void	_prod_command__2_free_cb(
			void *to_free,
			void *usrptr
			)
{
	command_destroy(to_free);
}

void	*_prod_command_simple__1_cb(
			t_lr_stack_item *item,
			void *usrptr
			)
{
	return (command_create((t_progname)item[0].data.derived.data));
}

void	_prod_command_simple__1_free_cb(
			void *to_free,
			void *usrptr
			)
{
	command_destroy(to_free);
}

void	*_prod_command_simple__2_cb(
			t_lr_stack_item *item,
			void *usrptr
			)
{
	return (command_create_args(item[0].data.derived.data,
			item[1].data.derived.data));
}

void	_prod_command_simple__2_free_cb(
			void *to_free,
			void *usrptr
			)
{
	command_destroy(to_free);
}

void	*_prod_args__1_cb(
			t_lr_stack_item *item,
			void *usrptr
			)
{
	return (args_create(item[0].data.token.data));
}

void	_prod_args__1_free_cb(
			void *to_free,
			void *usrptr
			)
{
	args_destroy(to_free);
}

void	*_prod_args__2_cb(
			t_lr_stack_item *item,
			void *usrptr
			)
{
	return (args_append(item[1].data.derived.data,
			item[0].data.token.data));
}

void	_prod_args__2_free_cb(
			void *to_free,
			void *usrptr
			)
{
	args_destroy(to_free);
}

void	*_prod_progname_cb(
			t_lr_stack_item *item,
			void *usrptr
			)
{
	return (ft_strdup(item[0].data.token.data));
}

void	_prod_progname_free_cb(
			void *to_free,
			void *usrptr
			)
{
	free(to_free);
}

void	*_prod_command_io__1_cb(
			t_lr_stack_item *item,
			void *usrptr
			)
{
	return (cio_create((t_io_info *)item[0].data.derived.data));
}

void	_prod_command_io__1_free_cb(
			void *to_free,
			void *usrptr
			)
{
	cio_destroy(to_free);
}

void	*_prod_command_io__2_cb(
			t_lr_stack_item *item,
			void *usrptr
			)
{
	if (cio_append((t_command_io *)item[1].data.derived.data,
			(t_io_info *)item[0].data.derived.data))
		return (NULL);
	return (item[1].data.derived.data);
}

void	_prod_command_io__2_free_cb(
			void *to_free,
			void *usrptr
			)
{
	cio_destroy(to_free);
}

void	*_prod_io_info_cb(
			t_lr_stack_item *item,
			void *usrptr
			)
{
	return (io_info_create(*(t_io_type *)(item[0].data.token.data),
		item[1].data.token.data));
}

void	_prod_io_info_free_cb(
			void *to_free,
			void *usrptr
			)
{
	io_info_destroy(to_free);
}
