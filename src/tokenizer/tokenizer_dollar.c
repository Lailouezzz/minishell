/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_dollar.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-boud <ale-boud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 16:46:48 by ale-boud          #+#    #+#             */
/*   Updated: 2024/03/11 19:34:47 by ale-boud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file tokenizer_dollar.c
 * @author ale-boud (ale-boud@student.42.fr)
 * @brief Dollar related tokenizer states.
 * @date 2024-03-11
 * @copyright Copyright (c) 2024
 */

// ************************************************************************** //
// *                                                                        * //
// * Includes.                                                              * //
// *                                                                        * //
// ************************************************************************** //

#include <libft.h>

#include "tokenizer/tokenizer.h"

// ************************************************************************** //
// *                                                                        * //
// * Header functions.                                                      * //
// *                                                                        * //
// ************************************************************************** //

t_ms_error	_state_dollar(
				t_lr_token_list *lrtoks,
				t_int_token *int_token
				)
{
	const char	*expended = _expand_dollar(&int_token->cur, int_token->env_ctx);
	int			r;

	if (ft_isspace(*expended))
	{
		if (int_token->word_read.str != NULL)
		{
			r = _flush_word_read(lrtoks, int_token);
			if (r != MS_OK)
				return (r);
		}
	}
	while (*expended != '\0')
	{
		while (ft_isspace(*expended))
			++expended;
		while (!ft_isspace(*expended) && *expended != '\0')
			if (dyn_str_pushback(&int_token->word_read, *(expended++)))
				return (MS_FATAL);
		if (ft_isspace(*expended))
			if (_flush_word_read(lrtoks, int_token))
				return (MS_FATAL);
	}
	return (MS_OK);
}

t_ms_error	_state_dollar_quoted(
				t_lr_token_list *lrtoks,
				t_int_token *int_token
				)
{
	const char	*expended;

	(void)(lrtoks);
	expended = _expand_dollar_doublequote(&int_token->cur, int_token->env_ctx);
	if (expended == NULL)
		return (MS_FATAL);
	if (*expended != '\0')
	{
		if (int_token->word_read.str != NULL)
			return (dyn_str_cat(&int_token->word_read, expended));
		else
			return (dyn_str_cat(&int_token->word_read, expended));
	}
	return (MS_OK);
}
