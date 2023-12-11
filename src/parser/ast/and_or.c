/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   and_or.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-boud <ale-boud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 21:34:22 by ale-boud          #+#    #+#             */
/*   Updated: 2023/12/11 21:45:34 by ale-boud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file and_or.c
 * @author ale-boud (ale-boud@student.42.fr)
 * @brief AST and or implementation.
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

t_and_or	*and_or_leaf(
				t_pipeline *pl
				)
{
	t_and_or	*and_or;

	and_or = malloc(sizeof(*and_or));
	if (and_or == NULL)
		return (pipeline_destroy(pl), NULL);
	and_or->right_pipeline = pl;
	and_or->logic_type = LOGIC_NONE;
	and_or->left = NULL;
	return (and_or);
}

t_and_or	*and_or_node(
				t_and_or *left,
				t_logic_type type,
				t_pipeline *pl
				)
{
	t_and_or	*and_or;

	and_or = malloc(sizeof(*and_or));
	if (and_or == NULL)
		return (pipeline_destroy(pl), and_or_destroy(left), NULL);
	and_or->right_pipeline = pl;
	and_or->logic_type = type;
	and_or->left = left;
	return (and_or);
}

void	and_or_destroy(
			t_and_or *and_or
			)
{
	if (and_or != NULL)
	{
		if (and_or->right_pipeline != NULL)
			pipeline_destroy(and_or->right_pipeline);
		if (and_or->left != NULL)
			and_or_destroy(and_or->left);
		free(and_or);
	}
}
