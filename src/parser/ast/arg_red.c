/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_red.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-boud <ale-boud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 19:49:44 by ale-boud          #+#    #+#             */
/*   Updated: 2023/12/11 22:57:48 by ale-boud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file arg_red.c
 * @author ale-boud (ale-boud@student.42.fr)
 * @brief AST arg red function.
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

t_arg_red	*arg_red_create_arg(
				char *arg
				)
{
	t_arg_red	*ar;

	ar = malloc(sizeof(*ar));
	if (ar == NULL)
		return (NULL);
	ar->type = AR_ARG;
	ar->data.arg = arg;
	return (ar);
}

t_arg_red	*arg_red_create_redirect(
				t_io_info *io_info
				)
{
	t_arg_red	*ar;

	ar = malloc(sizeof(*ar));
	if (ar == NULL)
		return (NULL);
	ar->type = AR_REDIRECT;
	ar->data.io_info = io_info;
	return (ar);
}

void	arg_red_destroy(
			t_arg_red *ar
			)
{
	if (ar->type == AR_ARG)
		free(ar->data.arg);
	else if (ar->type == AR_REDIRECT)
		io_info_destroy(ar->data.io_info);
}
