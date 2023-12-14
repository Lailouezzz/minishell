/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_io_and_or_pipe_end.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-boud <ale-boud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 03:13:18 by ale-boud          #+#    #+#             */
/*   Updated: 2023/12/14 03:15:14 by ale-boud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file word_io_and_or_pipe_end.c
 * @author ale-boud (ale-boud@student.42.fr)
 * @brief The word, io, and_or, pipe, end token generator.
 * @date 2023-12-14
 * @copyright Copyright (c) 2023
 */

// ************************************************************************** //
// *                                                                        * //
// * Includes.                                                              * //
// *                                                                        * //
// ************************************************************************** //

#include "tokenizer/tokenizer.h"

// ************************************************************************** //
// *                                                                        * //
// * Token generator.                                                       * //
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

int	_token_gen_end(
		t_lr_token *lrtok
		)
{
	lrtok->id = TOKEN_END;
	return (0);
}
