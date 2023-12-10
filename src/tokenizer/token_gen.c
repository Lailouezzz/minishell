/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_gen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-boud <ale-boud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 14:27:31 by ale-boud          #+#    #+#             */
/*   Updated: 2023/12/10 23:15:53 by ale-boud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file token_gen.c
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
// * The token free callbacks.                                              * //
// *                                                                        * //
// ************************************************************************** //

const t_lr_token_free_cb	g_tok_free_cbs[TOKEN__COUNT] = {
[TOKEN_WORD] = _token_free_word_cb,
[TOKEN_IO] = NULL,
[TOKEN_AND_OR] = NULL,
[TOKEN_PIPE] = NULL,
[TOKEN_OBRACKET] = NULL,
[TOKEN_CBRACKET] = NULL,
[TOKEN_END] = NULL,
};

// ************************************************************************** //
// *                                                                        * //
// * Token generator functions.                                             * //
// *                                                                        * //
// ************************************************************************** //

int	_token_gen_word(
		t_lr_token *lrtok,
		char *str
		)
{
	lrtok->id = TOKEN_WORD;
	lrtok->data.word = str;
	return (0);
}

int	_token_gen_io(
		t_lr_token *lrtok,
		t_io_type type
		)
{
	lrtok->id = TOKEN_IO;
	lrtok->data.io_type = type;
	return (0);
}

int	_token_gen_and_or(
		t_lr_token *lrtok,
		t_logic_type type
		)
{
	lrtok->id = TOKEN_AND_OR;
	lrtok->data.logic_type = type;
	return (0);
}

int	_token_gen_pipe(
		t_lr_token *lrtok
		)
{
	lrtok->id = TOKEN_PIPE;
	return (0);
}

int	_token_gen_obracket(
		t_lr_token *lrtok
		)
{
	lrtok->id = TOKEN_OBRACKET;
	return (0);
}

int	_token_gen_cbracket(
		t_lr_token *lrtok
		)
{
	lrtok->id = TOKEN_CBRACKET;
	return (0);
}

int	_token_gen_end(
		t_lr_token *lrtok
		)
{
	lrtok->id = TOKEN_END;
	return (0);
}

int	_token_gen_wildcard(
			t_lr_token *lrtok
			)
{
	lrtok->id = TOKEN__WILDCARD;
	return (0);
}

// ************************************************************************** //
// *                                                                        * //
// * Token free callback functions.                                         * //
// *                                                                        * //
// ************************************************************************** //

void	_token_free_word_cb(
			t_lr_token_type *data
			)
{
	free(data->word);
}
