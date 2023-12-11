/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subshell.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-boud <ale-boud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 21:32:44 by ale-boud          #+#    #+#             */
/*   Updated: 2023/12/11 21:52:31 by ale-boud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file subshell.c
 * @author ale-boud (ale-boud@student.42.fr)
 * @brief AST subshell function implementation.
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

t_subshell	*subshell_create(
				t_and_or *and_or
				)
{
	t_subshell	*ss;

	ss = malloc(sizeof(*ss));
	if (ss == NULL)
		return (and_or_destroy(and_or), NULL);
	ss->and_or = and_or;
	ss->redirect_list = NULL;
	return (ss);
}

int	subshell_add_rl(
		t_subshell *ss,
		t_redirect_list *rl
		)
{
	if (ss == NULL)
		return (1);
	ss->redirect_list = rl;
	return (0);
}

void	subshell_destroy(
			t_subshell *ss
			)
{
	if (ss != NULL)
	{
		if (ss->redirect_list != NULL)
			redirect_list_destroy(ss->redirect_list);
		if (ss->and_or != NULL)
			and_or_destroy(ss->and_or);
		free(ss);
	}
}
