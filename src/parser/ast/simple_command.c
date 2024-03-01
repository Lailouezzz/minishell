/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-boud <ale-boud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 21:11:45 by ale-boud          #+#    #+#             */
/*   Updated: 2024/02/13 17:24:40 by ale-boud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file simple_command.c
 * @author ale-boud (ale-boud@student.42.fr)
 * @brief AST simple command implementation.
 * @date 2023-12-11
 * @copyright Copyright (c) 2023
 */

// ************************************************************************** //
// *                                                                        * //
// * Includes.                                                              * //
// *                                                                        * //
// ************************************************************************** //

#include <libft.h>

#include "parser/ast.h"

// ************************************************************************** //
// *                                                                        * //
// * Header function.                                                       * //
// *                                                                        * //
// ************************************************************************** //

t_simple_command	*simple_command_create(
						t_progname pn
						)
{
	t_simple_command	*sc;
	char				*pncpy;

	sc = malloc(sizeof(*sc));
	if (sc == NULL)
		return (free(pn), NULL);
	pncpy = ft_strdup(pn);
	if (pncpy == NULL)
		return (free(pn), free(sc), NULL);
	sc->args = args_create(pncpy);
	if (sc->args == NULL)
		return (free(pn), free(sc), free(pncpy), NULL);
	sc->redirect_list = NULL;
	sc->pn = pn;
	return (sc);
}

int	simple_command_add_rl(
		t_simple_command *sc,
		t_redirect_list *rl
		)
{
	if (sc == NULL)
		return (1);
	if (sc->redirect_list == NULL)
	{
		sc->redirect_list = rl;
		return (0);
	}
	if (redirect_list_cat(sc->redirect_list, rl))
		return (free(sc->pn), args_destroy(sc->args), free(sc), 1);
	return (0);
}

int	simple_command_add_arl(
		t_simple_command *sc,
		t_args_redirect_list *arl
		)
{
	if (sc == NULL)
		return (1);
	if (simple_command_add_rl(sc, arl->redirect_list))
		return (args_destroy(arl->args), free(arl), 1);
	if (sc->args == NULL)
	{
		sc->args = arl->args;
		free(arl);
		return (0);
	}
	if (args_cat(sc->args, arl->args))
		return (free(sc->pn), redirect_list_destroy(sc->redirect_list),
			free(sc), free(arl), 1);
	free(arl);
	return (0);
}

void	simple_command_destroy(
			t_simple_command *sc
			)
{
	if (sc != NULL)
	{
		if (sc->pn != NULL)
			free(sc->pn);
		args_destroy(sc->args);
		redirect_list_destroy(sc->redirect_list);
		free(sc);
	}
}
