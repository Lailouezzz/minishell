/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_initial.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-boud <ale-boud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 16:41:51 by ale-boud          #+#    #+#             */
/*   Updated: 2024/03/11 19:58:53 by ale-boud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file tokenizer_initial.c
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2024-03-11
 * 
 * @copyright Copyright (c) 2024
 * 
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
// * Helper prototype.                                                      * //
// *                                                                        * //
// ************************************************************************** //

static t_ms_error	__state_initial_like_norminette(
						t_lr_token_list *lrtoks,
						t_int_token *int_token,
						char current
						);

// ************************************************************************** //
// *                                                                        * //
// * Header functions.                                                      * //
// *                                                                        * //
// ************************************************************************** //

t_ms_error	_state_initial(
				t_lr_token_list *lrtoks,
				t_int_token *int_token
				)
{
	const char	current = *int_token->cur;
	t_lr_token	lrtok;

	if (current == '\0')
		return (_token_gen_end(&lrtok) || lrtoks_pushback(lrtoks, &lrtok));
	++int_token->cur;
	if (current == '|')
		return (_state_pipe_or(lrtoks, int_token));
	if (current == '&')
		return (_state_and(lrtoks, int_token));
	if (current == '<')
		return (_state_in(lrtoks, int_token));
	if (current == '>')
		return (_state_out(lrtoks, int_token));
	return (__state_initial_like_norminette(lrtoks, int_token, current));
}

// ************************************************************************** //
// *                                                                        * //
// * Helper implementation.                                                 * //
// *                                                                        * //
// ************************************************************************** //

static t_ms_error	__state_initial_like_norminette(
						t_lr_token_list *lrtoks,
						t_int_token *int_token,
						char current
						)
{
	t_lr_token	lrtok;
	t_ms_error	r;

	if (current == '(')
		return (_token_gen_obracket(&lrtok) || lrtoks_pushback(lrtoks, &lrtok));
	if (current == ')')
		return (_token_gen_cbracket(&lrtok) || lrtoks_pushback(lrtoks, &lrtok));
	if (current == '*' && (ft_ismeta(*int_token->cur)
			|| ft_isspace(*int_token->cur) || *int_token->cur == '\0'))
		return (_state_wildcard(lrtoks, int_token));
	if (current == '$')
	{
		r = _state_dollar(lrtoks, int_token);
		if (r != MS_OK)
			return (r);
	}
	if (current == '"')
		return (_state_doublequote(lrtoks, int_token));
	if (current == '\'')
		return (_state_quote(lrtoks, int_token));
	if (current != '$' && dyn_str_pushback(&int_token->word_read, current))
		return (MS_FATAL);
	return (_state_word(lrtoks, int_token));
}
