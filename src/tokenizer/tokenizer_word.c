/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_word.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-boud <ale-boud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 16:46:20 by ale-boud          #+#    #+#             */
/*   Updated: 2024/03/11 16:50:15 by ale-boud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file tokenizer_word.c
 * @author ale-boud (ale-boud@student.42.fr)
 * @brief Word related tokenizer states.
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

t_ms_error	_state_word(
				t_lr_token_list *lrtoks,
				t_int_token *int_token
				)
{
	char		current;
	t_ms_error	r;

	current = *int_token->cur;
	while (current != '\0' && !ft_ismeta(current) && !ft_isspace(current))
	{
		++int_token->cur;
		if (current == '"')
			return (_state_doublequote(lrtoks, int_token));
		if (current == '\'')
			return (_state_quote(lrtoks, int_token));
		if (current == '$')
			r = _state_dollar(lrtoks, int_token);
		else
			r = dyn_str_pushback(&int_token->word_read, current);
		if (r != MS_OK)
			return (r);
		current = *int_token->cur;
	}
	if (int_token->word_read.str != NULL)
		return (_flush_word_read(lrtoks, int_token));
	return (MS_OK);
}

t_ms_error	_state_quote(
				t_lr_token_list *lrtoks,
				t_int_token *int_token
				)
{
	char	current;
	int		r;

	current = *int_token->cur;
	r = _init_dyn_str_if_null(int_token);
	if (r != MS_OK)
		return (r);
	while (current != '\'')
	{
		++int_token->cur;
		if (current == '\0')
			return (MS_SYNTAX_ERROR);
		r = dyn_str_pushback(&int_token->word_read, current);
		if (r != MS_OK)
			return (r);
		current = *int_token->cur;
	}
	++int_token->cur;
	return (_state_word(lrtoks, int_token));
}

t_ms_error	_state_doublequote(
				t_lr_token_list *lrtoks,
				t_int_token *int_token
				)
{
	char	current;
	int		r;

	current = *int_token->cur;
	r = _init_dyn_str_if_null(int_token);
	if (r != MS_OK)
		return (r);
	while (current != '\"')
	{
		++int_token->cur;
		if (current == '\0')
			return (MS_SYNTAX_ERROR);
		if (current == '$')
			r = _state_dollar_quoted(lrtoks, int_token);
		else
			r = dyn_str_pushback(&int_token->word_read, current);
		if (r != MS_OK)
			return (r);
		current = *int_token->cur;
	}
	++int_token->cur;
	return (_state_word(lrtoks, int_token));
}
