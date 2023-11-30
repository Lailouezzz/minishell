/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-boud <ale-boud@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 14:12:05 by ale-boud          #+#    #+#             */
/*   Updated: 2023/11/30 14:42:21 by ale-boud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file tokenizer.h
 * @author ale-boud (ale-boud@student.42lehavre.fr)
 * @brief The tokenizer definition.
 * @date 2023-11-30
 * @copyright Copyright (c) 2023
 */

#ifndef TOKENIZER_H
# define TOKENIZER_H

// ************************************************************************** //
// *                                                                        * //
// * Includes.                                                              * //
// *                                                                        * //
// ************************************************************************** //

# include <stdlib.h>

# include <lr_token.h>

# include "token.h"

// ************************************************************************** //
// *                                                                        * //
// * Structure definitions.                                                 * //
// *                                                                        * //
// ************************************************************************** //

typedef struct s_int_token {
	t_lr_token_id	id;
	const char		*start;
	size_t			len;
}	t_int_token;

typedef int	(*t_token_gen_cb)(t_lr_token *rtok, const t_int_token *int_token);

// ************************************************************************** //
// *                                                                        * //
// * Token generator callback table definition.                             * //
// *                                                                        * //
// ************************************************************************** //

extern const t_token_gen_cb	g_tok_gen_cbs[TOKEN__COUNT];

// ************************************************************************** //
// *                                                                        * //
// * Token generator callbacks prototypes.                                  * //
// *                                                                        * //
// ************************************************************************** //

int	_token_gen_word_cb(
		t_lr_token *rtok,
		const t_int_token *int_token
		);

int	_token_gen_io_cb(
		t_lr_token *rtok,
		const t_int_token *int_token
		);

int	_token_gen_end_cb(
		t_lr_token *rtok,
		const t_int_token *int_token
		);

// ************************************************************************** //
// *                                                                        * //
// * Function prototypes.                                                   * //
// *                                                                        * //
// ************************************************************************** //

#endif
