/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_helpers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-boud <ale-boud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 16:37:52 by ale-boud          #+#    #+#             */
/*   Updated: 2024/03/11 16:50:59 by ale-boud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file tokenizer_helpers.c
 * @author ale-boud (ale-boud@student.42.fr)
 * @brief Tokenizer helpers functions.
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

int	ft_ismeta(
		char c
		)
{
	return (c == '|' || c == '&' || c == '>' || c == '<' || c == '('
		|| c == ')');
}

const char	*_expand_dollar(
				const char **start,
				t_env_ctx *env_ctx
				)
{
	static const char	*dollar = "$";
	static const char	*void_str = "";
	const char			*var;
	t_dyn_str			dyn_str;

	if (ft_ismeta(**start) || ft_isspace(**start) || **start == '\0')
		return (dollar);
	if (**start == '\'' || **start == '"')
		return (void_str);
	if (**start == '?')
		return (++(*start), env_ctx->current_code_str);
	if (dyn_str_init(&dyn_str) != MS_OK)
		return (NULL);
	while (ft_isalnum(**start) && **start != '\0')
	{
		if (dyn_str_pushback(&dyn_str, **start) != MS_OK)
			return (NULL);
		++(*start);
	}
	var = env_ctx_get_variable(env_ctx, dyn_str.str);
	dyn_str_destroy(&dyn_str);
	if (var == NULL)
		return (void_str);
	return (var);
}

t_ms_error	_flush_word_read(
				t_lr_token_list *lrtoks,
				t_int_token *int_token
				)
{
	t_lr_token	lrtok;
	int			r;

	if (_token_gen_word(&lrtok, int_token->word_read.str))
		return (MS_FATAL);
	r = lrtoks_pushback(lrtoks, &lrtok);
	if (r != MS_OK)
		return (r);
	int_token->word_read.str = NULL;
	return (MS_OK);
}

t_ms_error	_init_dyn_str_if_null(
				t_int_token *int_token
				)
{
	int		r;

	if (int_token->word_read.str == NULL)
	{
		r = dyn_str_init(&int_token->word_read);
		if (r != MS_OK)
			return (r);
	}
	return (MS_OK);
}
