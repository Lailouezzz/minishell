/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bracket.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-boud <ale-boud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 03:13:18 by ale-boud          #+#    #+#             */
/*   Updated: 2023/12/14 03:13:54 by ale-boud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file bracket.c
 * @author ale-boud (ale-boud@student.42.fr)
 * @brief The bracket token generator.
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
