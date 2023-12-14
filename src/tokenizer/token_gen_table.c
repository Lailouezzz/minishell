/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_gen_table.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-boud <ale-boud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 14:27:31 by ale-boud          #+#    #+#             */
/*   Updated: 2023/12/14 03:21:12 by ale-boud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file token_gen_table.c
 * @author ale-boud (ale-boud@student.42lehavre.fr)
 * @brief The token generator table.
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
