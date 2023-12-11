/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_redirect_list.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-boud <ale-boud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 19:40:38 by ale-boud          #+#    #+#             */
/*   Updated: 2023/12/11 23:41:16 by ale-boud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file args_redirect_list.c
 * @author ale-boud (ale-boud@student.42.fr)
 * @brief AST args redirect function implementation.
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

t_args_redirect_list	*args_redirect_list_init(void)
{
	t_args_redirect_list	*arl;

	arl = malloc(sizeof(*arl));
	if (arl == NULL)
		return (NULL);
	arl->args = NULL;
	arl->redirect_list = redirect_list_init();
	if (arl->redirect_list == NULL)
		return (free(arl), NULL);
	arl->args = args_init();
	if (arl->args == NULL)
		return (redirect_list_destroy(arl->redirect_list), free(arl), NULL);
	return (arl);
}

t_args_redirect_list	*args_redirect_list_create(
							t_arg_red *ar
							)
{
	t_args_redirect_list	*arl;

	arl = malloc(sizeof(*arl));
	if (arl == NULL)
		return (NULL);
	arl->args = NULL;
	arl->redirect_list = redirect_list_init();
	if (arl->redirect_list == NULL)
		return (free(arl), NULL);
	arl->args = args_init();
	if (arl->args == NULL)
		return (redirect_list_destroy(arl->redirect_list), free(arl), NULL);
	if (args_redirect_list_pusback(arl, ar))
		return (NULL);
	return (arl);
}

int	args_redirect_list_pusback(
							t_args_redirect_list *arl,
							t_arg_red *ar
							)
{
	if (ar->type == AR_ARG)
	{
		if (args_pushback(arl->args, ar->data.arg))
			return (redirect_list_destroy(arl->redirect_list), free(arl), 1);
	}
	else if (ar->type == AR_REDIRECT)
	{
		if (redirect_list_pushback(arl->redirect_list, ar->data.io_info))
			return (args_destroy(arl->args), free(arl), 1);
	}
	free(ar);
	return (0);
}

void	args_redirect_list_destroy(
			t_args_redirect_list *arl
			)
{
	if (arl != NULL)
	{
		if (arl->args != NULL)
			args_destroy(arl->args);
		if (arl->redirect_list != NULL)
			redirect_list_destroy(arl->redirect_list);
		free(arl);
	}
}
