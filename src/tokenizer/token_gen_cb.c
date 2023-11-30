/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_gen_cb.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-boud <ale-boud@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 14:27:31 by ale-boud          #+#    #+#             */
/*   Updated: 2023/11/30 17:14:34 by ale-boud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file token_gen_cb.c
 * @author ale-boud (ale-boud@student.42lehavre.fr)
 * @brief The token generator callbacks implementation.
 * @date 2023-11-30
 * @copyright Copyright (c) 2023
 */

// ************************************************************************** //
// *                                                                        * //
// * Includes.                                                              * //
// *                                                                        * //
// ************************************************************************** //

#include <stdlib.h>

#include "tokenizer/tokenizer.h"
#include "utils.h"

// ************************************************************************** //
// *                                                                        * //
// * The production callbacks.                                              * //
// *                                                                        * //
// ************************************************************************** //

const t_token_gen_cb	g_tok_gen_cbs[TOKEN__COUNT] = {
[TOKEN_WORD] = _token_gen_word_cb,
[TOKEN_IO] = _token_gen_io_cb,
[TOKEN_END] = _token_gen_end_cb,
};

const t_token_free_cb	g_tok_free_cbs[TOKEN__COUNT] = {
[TOKEN_WORD] = free,
[TOKEN_IO] = NULL,
[TOKEN_END] = NULL,
};

// ************************************************************************** //
// *                                                                        * //
// * Callback functions.                                                    * //
// *                                                                        * //
// ************************************************************************** //

int	_token_gen_word_cb(
		t_lr_token *lrtok,
		const t_int_token *int_token
		)
{
	char	*pstr;

	lrtok->id = TOKEN_WORD;
	pstr = malloc(int_token->len + 1);
	if (pstr == NULL)
		return (1);
	ft_memcpy(pstr, int_token->start, int_token->len);
	pstr[int_token->len] = '\0';
	lrtok->data = pstr;
	return (0);
}

int	_token_gen_io_cb(
		t_lr_token *lrtok,
		const t_int_token *int_token
		)
{
	const char *const	start = int_token->start;

	lrtok->id = TOKEN_IO;
	if (int_token->len == 1)
	{
		if (*start == '>')
			lrtok->data = &(static t_io_type){IO_OUT};
		else if (*start == '<')
			lrtok->data = &(static t_io_type){IO_IN};
		else
			return (1);
	}
	else if (int_token->len == 2)
	{
		if (start[0] == '>' && start[1] == '>')
			lrtok->data = &(static t_io_type){IO_APPEND};
		else if (start[0] == '<' && start[1] == '<')
			lrtok->data = &(static t_io_type){IO_HEREDOC};
		else
			return (1);
	}
	return (0);
}

int	_token_gen_end_cb(
		t_lr_token *lrtok,
		const t_int_token *int_token
		)
{
	(void)(int_token);
	lrtok->id = TOKEN_END;
	lrtok->data = NULL;
	return (0);
}
