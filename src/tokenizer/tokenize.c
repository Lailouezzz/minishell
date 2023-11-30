/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-boud <ale-boud@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 15:22:16 by ale-boud          #+#    #+#             */
/*   Updated: 2023/11/30 16:49:12 by ale-boud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file tokenize.c
 * @author ale-boud (ale-boud@student.42lehavre.fr)
 * @brief The tokenize implementation.
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
// * States function prototypes.                                            * //
// *                                                                        * //
// ************************************************************************** //

static int	_state_initial(
				t_lr_token *lrtok,
				t_int_token *int_token
				);

static int	_state_out(
				t_lr_token *lrtok,
				t_int_token *int_token
				);

static int	_state_in(
				t_lr_token *lrtok,
				t_int_token *int_token
				);

static int	_state_word(
				t_lr_token *lrtok,
				t_int_token *int_token
				);

// ************************************************************************** //
// *                                                                        * //
// * Header functions.                                                      * //
// *                                                                        * //
// ************************************************************************** //

int	tokenize(
		t_lr_token *lrtok,
		const char **start
		)
{
	t_int_token	int_token;
	int			r;

	int_token.start = *start;
	while (ft_isspace(*int_token.start) && *int_token.start != '\0')
		++int_token.start;
	int_token.len = 0;
	r = _state_initial(lrtok, &int_token);
	*start = int_token.start + int_token.len;
	return (r);
}

// ************************************************************************** //
// *                                                                        * //
// * State functions implementation.                                        * //
// *                                                                        * //
// ************************************************************************** //

static int	_state_initial(
		t_lr_token *lrtok,
		t_int_token *int_token
		)
{
	if (*int_token->start == '\0')
		return (g_tok_gen_cbs[TOKEN_END](lrtok, int_token));
	++int_token->len;
	if (*int_token->start == '\n')
		return (g_tok_gen_cbs[TOKEN_END](lrtok, int_token));
	else if (*int_token->start == '>')
		return (_state_out(lrtok, int_token));
	else if (*int_token->start == '<')
		return (_state_in(lrtok, int_token));
	return (_state_word(lrtok, int_token));
}

static int	_state_out(
		t_lr_token *lrtok,
		t_int_token *int_token
		)
{
	const char	current = int_token->start[int_token->len];

	if (ft_isspace(current)
		|| current == '\0')
		return (g_tok_gen_cbs[TOKEN_IO](lrtok, int_token));
	++int_token->len;
	if (current == '>')
		return (g_tok_gen_cbs[TOKEN_IO](lrtok, int_token));
	return (_state_word(lrtok, int_token));
}
static int	_state_in(
		t_lr_token *lrtok,
		t_int_token *int_token
		)
{
	const char	current = int_token->start[int_token->len];

	if (ft_isspace(current)
		|| current == '\0')
		return (g_tok_gen_cbs[TOKEN_IO](lrtok, int_token));
	++int_token->len;
	if (current == '<')
		return (g_tok_gen_cbs[TOKEN_IO](lrtok, int_token));
	return (_state_word(lrtok, int_token));
}

static int	_state_word(
		t_lr_token *lrtok,
		t_int_token *int_token
		)
{
	while (!ft_isspace(int_token->start[int_token->len])
		&& int_token->start[int_token->len] != '\0')
		++int_token->len;
	return (g_tok_gen_cbs[TOKEN_WORD](lrtok, int_token));
}
