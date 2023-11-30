/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-boud <ale-boud@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 16:41:44 by ale-boud          #+#    #+#             */
/*   Updated: 2023/11/30 17:39:42 by ale-boud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file tokenizer.c
 * @author ale-boud (ale-boud@student.42lehavre.fr)
 * @brief The tokenizer implementation.
 * @date 2023-11-30
 * @copyright Copyright (c) 2023
 */

// ************************************************************************** //
// *                                                                        * //
// * Includes.                                                              * //
// *                                                                        * //
// ************************************************************************** //

#include "tokenizer/tokenizer.h"
#include "utils.h"

// ************************************************************************** //
// *                                                                        * //
// * Helper function prototypes.                                            * //
// *                                                                        * //
// ************************************************************************** //

static t_token_list	*_tokenizer_init(void);

static int			_tokenizer_add(
						t_token_list *lrtoks,
						const t_lr_token *lrtok
						);

// ************************************************************************** //
// *                                                                        * //
// * Header functions.                                                      * //
// *                                                                        * //
// ************************************************************************** //

t_token_list	*tokenizer(
					const char *str
					)
{
	t_lr_token		lrtok;
	t_token_list	*lrtoks;

	lrtoks = _tokenizer_init();
	if (lrtoks == NULL)
		return (NULL);
	while (*str != '\0')
	{
		if (tokenize(&lrtok, &str) || _tokenizer_add(lrtoks, &lrtok))
		{
			token_list_destoy(lrtoks);
			return (NULL);
		}
	}
	if (lrtoks->used == 0 || lrtoks->lrtoks[lrtoks->used - 1].id != TOKEN_END)
	{
		if (_tokenizer_add(lrtoks, &(static const t_lr_token){TOKEN_END, NULL}))
		{
			token_list_destoy(lrtoks);
			return (NULL);
		}
	}
	return (lrtoks);
}

void	token_list_destoy(
			t_token_list *lrtoks
			)
{
	size_t	k;

	if (lrtoks != NULL)
	{
		if (lrtoks->lrtoks != NULL)
		{
			k = 0;
			while (k < lrtoks->used)
			{
				if (g_tok_free_cbs[lrtoks->lrtoks[k].id] != NULL)
					g_tok_free_cbs[lrtoks->lrtoks[k].id](
						lrtoks->lrtoks[k].data);
				++k;
			}
			free(lrtoks->lrtoks);
		}
		free(lrtoks);
	}
}

// ************************************************************************** //
// *                                                                        * //
// * Helper function.                                                       * //
// *                                                                        * //
// ************************************************************************** //

static t_token_list	*_tokenizer_init(void)
{
	t_token_list	*lrtoks;

	lrtoks = malloc(sizeof(*lrtoks));
	if (lrtoks == NULL)
		return (NULL);
	lrtoks->alloced = 1;
	lrtoks->used = 0;
	lrtoks->lrtoks = malloc(sizeof(*lrtoks->lrtoks) * lrtoks->alloced);
	if (lrtoks->lrtoks == NULL)
	{
		free(lrtoks);
		return (NULL);
	}
	return (lrtoks);
}

static int	_tokenizer_add(
				t_token_list *lrtoks,
				const t_lr_token *lrtok
				)
{
	if (lrtoks->used >= lrtoks->alloced)
	{
		lrtoks->lrtoks = ft_realloc(lrtoks->lrtoks,
				lrtoks->alloced * sizeof(*lrtoks->lrtoks),
				lrtoks->alloced * sizeof(*lrtoks->lrtoks) * 2);
		if (lrtoks->lrtoks == NULL)
			return (1);
		lrtoks->alloced *= 2;
	}
	ft_memcpy(lrtoks->lrtoks + lrtoks->used, lrtok, sizeof(*lrtok));
	++lrtoks->used;
	return (0);
}
