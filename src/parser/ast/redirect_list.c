/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-boud <ale-boud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 19:54:32 by ale-boud          #+#    #+#             */
/*   Updated: 2024/02/13 17:44:54 by ale-boud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file redirect_list.c
 * @author ale-boud (ale-boud@student.42.fr)
 * @brief AST redirect list implementation.
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

#include "utils.h"

// ************************************************************************** //
// *                                                                        * //
// * Header function.                                                       * //
// *                                                                        * //
// ************************************************************************** //

t_redirect_list	*redirect_list_init(void)
{
	t_redirect_list	*rl;

	rl = malloc(sizeof(*rl));
	if (rl == NULL)
		return (NULL);
	rl->used = 0;
	rl->alloced = 1;
	rl->io_infos = malloc(sizeof(*rl->io_infos) * rl->alloced);
	if (rl->io_infos == NULL)
		return (free(rl), NULL);
	return (rl);
}

t_redirect_list	*redirect_list_create(
					t_io_info *io_info
					)
{
	t_redirect_list	*rl;

	rl = malloc(sizeof(*rl));
	if (rl == NULL)
		return (io_info_destroy(io_info), NULL);
	rl->used = 1;
	rl->alloced = 1;
	rl->io_infos = malloc(sizeof(*rl->io_infos) * rl->alloced);
	if (rl->io_infos == NULL)
		return (free(rl), io_info_destroy(io_info), NULL);
	rl->io_infos[0] = *io_info;
	free(io_info);
	return (rl);
}

int	redirect_list_pushback(
		t_redirect_list *rl,
		t_io_info *io_info
		)
{
	t_io_info	*tmp;

	if (rl->used >= rl->alloced)
	{
		tmp = _realloc(rl->io_infos,
				rl->alloced * sizeof(*rl->io_infos),
				rl->alloced * 2 * sizeof(*rl->io_infos));
		if (tmp == NULL)
			return (redirect_list_destroy(rl), io_info_destroy(io_info), 1);
		rl->alloced *= 2;
		rl->io_infos = tmp;
	}
	rl->io_infos[rl->used++] = *io_info;
	free(io_info);
	return (0);
}

int	redirect_list_cat(
		t_redirect_list *rl1,
		t_redirect_list *rl2
		)
{
	t_io_info	*tmp;
	size_t		total_size;

	total_size = rl1->used + rl2->used;
	if (total_size > rl1->alloced)
	{
		tmp = _realloc(rl1->io_infos,
				rl1->alloced * sizeof(*rl1->io_infos),
				total_size * sizeof(*rl1->io_infos));
		if (tmp == NULL)
			return (redirect_list_destroy(rl1), redirect_list_destroy(rl2), 1);
		rl1->alloced = total_size;
		rl1->io_infos = tmp;
	}
	ft_memcpy(rl1->io_infos + rl1->used, rl2->io_infos,
		rl2->used * sizeof(*rl2->io_infos));
	rl2->used = 0;
	rl1->used = total_size;
	redirect_list_destroy(rl2);
	return (0);
}

void	redirect_list_destroy(
		t_redirect_list *rl
		)
{
	size_t	k;

	if (rl != NULL)
	{
		if (rl->io_infos != NULL)
		{
			k = 0;
			while (k < rl->used)
			{
				free(rl->io_infos[k].file);
				++k;
			}
			free(rl->io_infos);
		}
		free(rl);
	}
}
