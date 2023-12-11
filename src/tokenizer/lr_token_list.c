/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lr_token_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-boud <ale-boud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 13:52:39 by ale-boud          #+#    #+#             */
/*   Updated: 2023/12/11 16:53:51 by ale-boud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file lr_token_list.c
 * @author ale-boud (ale-boud@student.42.fr)
 * @brief Implementation of lr_token dynamic list.
 * @date 2023-12-11
 * @copyright Copyright (c) 2023
 */

// ************************************************************************** //
// *                                                                        * //
// * Includes.                                                              * //
// *                                                                        * //
// ************************************************************************** //

#include "tokenizer/lr_token_list.h"
#include "tokenizer/tokenizer.h"
#include "utils.h"

// ************************************************************************** //
// *                                                                        * //
// * Header function.                                                       * //
// *                                                                        * //
// ************************************************************************** //

int	lrtoks_init(
		t_lr_token_list *lrtoks
		)
{
	lrtoks->used = 0;
	lrtoks->alloced = 1;
	lrtoks->lrtoks = malloc(sizeof(*lrtoks->lrtoks) * lrtoks->alloced);
	if (lrtoks->lrtoks == NULL)
		return (1);
	return (0);
}

int	lrtoks_pushback(
		t_lr_token_list *lrtoks,
		const t_lr_token *lrtok
		)
{
	void	*tmp;

	if (lrtoks->used >= lrtoks->alloced)
	{
		tmp = lrtoks->lrtoks;
		lrtoks->lrtoks = ft_realloc(lrtoks->lrtoks,
				lrtoks->alloced * sizeof(*lrtoks->lrtoks),
				lrtoks->alloced * sizeof(*lrtoks->lrtoks) * 2);
		if (lrtoks->lrtoks == NULL)
		{
			free(tmp);
			return (1);
		}
		lrtoks->alloced *= 2;
	}
	lrtoks->lrtoks[lrtoks->used++] = *lrtok;
	return (0);
}

void	lrtoks_destroy(
			t_lr_token_list *lrtoks
			)
{
	size_t	k;

	k = 0;
	while (k < lrtoks->used)
	{
		if (g_tok_free_cbs[lrtoks->lrtoks[k].id] != NULL)
			g_tok_free_cbs[lrtoks->lrtoks[k].id](&lrtoks->lrtoks[k].data);
		++k;
	}
	if (lrtoks->lrtoks != NULL)
		free(lrtoks->lrtoks);
}

t_lr_token	*lrtoks_end(
				t_lr_token_list *lrtoks
				)
{
	if (lrtoks->lrtoks == NULL)
		return (NULL);
	return (lrtoks->lrtoks + lrtoks->used - 1);
}

size_t	lrtoks_size(
			t_lr_token_list *lrtoks
			)
{
	return (lrtoks->used);
}
