/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-boud <ale-boud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 22:32:42 by ale-boud          #+#    #+#             */
/*   Updated: 2023/12/11 22:32:52 by ale-boud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file command_line.c
 * @author ale-boud (ale-boud@student.42.fr)
 * @brief AST command line function implementation.
 * @date 2023-12-11
 * @copyright Copyright (c) 2023
 */

// ************************************************************************** //
// *                                                                        * //
// * Includes.                                                              * //
// *                                                                        * //
// ************************************************************************** //

#include "parser/ast.h"

// ************************************************************************** //
// *                                                                        * //
// * Header function.                                                       * //
// *                                                                        * //
// ************************************************************************** //

t_command_line	*command_line_create(
					t_and_or *and_or
					)
{
	t_command_line	*cl;

	cl = malloc(sizeof(*cl));
	if (cl == NULL)
		return (and_or_destroy(and_or), NULL);
	cl->and_or = and_or;
	return (cl);
}

void	command_line_destroy(
			t_command_line *cl
			)
{
	if (cl != NULL)
	{
		if (cl->and_or != NULL)
			and_or_destroy(cl->and_or);
		free(cl);
	}
}
