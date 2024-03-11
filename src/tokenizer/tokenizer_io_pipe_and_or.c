/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_io_pipe_and_or.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-boud <ale-boud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 16:47:45 by ale-boud          #+#    #+#             */
/*   Updated: 2024/03/11 16:49:18 by ale-boud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file tokenizer_io_pipe_and_or.c
 * @author ale-boud (ale-boud@student.42.fr)
 * @brief IO, pipe, and, or related tokenizer states.
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

t_ms_error	_state_out(
				t_lr_token_list *lrtoks,
				t_int_token *int_token
				)
{
	const char	current = *int_token->cur;
	t_lr_token	lrtok;

	if (current == '>')
	{
		++int_token->cur;
		if (_token_gen_io(&lrtok, IO_APPEND))
			return (MS_FATAL);
		return (lrtoks_pushback(lrtoks, &lrtok));
	}
	if (_token_gen_io(&lrtok, IO_OUT))
		return (MS_FATAL);
	return (lrtoks_pushback(lrtoks, &lrtok));
}

t_ms_error	_state_in(
				t_lr_token_list *lrtoks,
				t_int_token *int_token
				)
{
	const char	current = *int_token->cur;
	t_lr_token	lrtok;

	if (current == '<')
	{
		++int_token->cur;
		if (_token_gen_io(&lrtok, IO_HEREDOC))
			return (MS_FATAL);
		return (lrtoks_pushback(lrtoks, &lrtok));
	}
	if (_token_gen_io(&lrtok, IO_IN))
		return (MS_FATAL);
	return (lrtoks_pushback(lrtoks, &lrtok));
}

t_ms_error	_state_pipe_or(
				t_lr_token_list *lrtoks,
				t_int_token *int_token
				)
{
	const char	current = *int_token->cur;
	t_lr_token	lrtok;

	if (current == '|')
	{
		++int_token->cur;
		if (_token_gen_and_or(&lrtok, LOGIC_OR))
			return (MS_FATAL);
		return (lrtoks_pushback(lrtoks, &lrtok));
	}
	if (_token_gen_pipe(&lrtok))
		return (MS_FATAL);
	return (lrtoks_pushback(lrtoks, &lrtok));
}

t_ms_error	_state_and(
				t_lr_token_list *lrtoks,
				t_int_token *int_token
				)
{
	const char	current = *int_token->cur;
	t_lr_token	lrtok;

	if (current != '&')
		return (MS_SYNTAX_ERROR);
	++int_token->cur;
	if (_token_gen_and_or(&lrtok, LOGIC_AND))
		return (MS_FATAL);
	return (lrtoks_pushback(lrtoks, &lrtok));
}
