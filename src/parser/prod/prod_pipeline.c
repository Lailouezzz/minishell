/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prod_pipeline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-boud <ale-boud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 02:45:18 by ale-boud          #+#    #+#             */
/*   Updated: 2023/12/14 02:55:07 by ale-boud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file prod_pipeline.c
 * @author ale-boud (ale-boud@student.42.fr)
 * @brief Prod callback for #s_pipeline.
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

void	*_prod_pipeline__1(
			t_lr_stack_item *item,
			void *usrptr
			)
{
	t_command *const	command = item[0].data.derived.data;

	(void)(usrptr);
	return (pipeline_create(command));
}

void	_free_pipeline__1(
			void *to_free,
			void *usrptr
			)
{
	(void)(usrptr);
	pipeline_destroy(to_free);
}

void	*_prod_pipeline__3(
			t_lr_stack_item *item,
			void *usrptr
			)
{
	t_pipeline *const	pl = item[0].data.derived.data;
	t_command *const	command = item[2].data.derived.data;

	(void)(usrptr);
	if (pipeline_pushback(pl, command))
		return (NULL);
	return (pl);
}

void	_free_pipeline__3(
			void *to_free,
			void *usrptr
			)
{
	(void)(usrptr);
	pipeline_destroy(to_free);
}
