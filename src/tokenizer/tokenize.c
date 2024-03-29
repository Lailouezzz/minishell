/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-boud <ale-boud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 15:22:16 by ale-boud          #+#    #+#             */
/*   Updated: 2024/03/11 16:50:03 by ale-boud         ###   ########.fr       */
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

#include <libft.h>

#include "tokenizer/tokenizer.h"

// ************************************************************************** //
// *                                                                        * //
// * Header functions.                                                      * //
// *                                                                        * //
// ************************************************************************** //

t_ms_error	tokenize(
				t_lr_token_list *lrtoks,
				t_env_ctx *env_ctx,
				const char **start
				)
{
	t_int_token	int_token;
	int			r;

	r = lrtoks_init(lrtoks);
	if (r != MS_OK)
		return (r);
	int_token.cur = *start;
	int_token.env_ctx = env_ctx;
	int_token.word_read.str = NULL;
	while (ft_isspace(*int_token.cur) && *int_token.cur != '\0')
		++int_token.cur;
	r = _state_initial(lrtoks, &int_token);
	if (r != MS_OK)
	{
		lrtoks_destroy(lrtoks);
		dyn_str_destroy(&int_token.word_read);
	}
	*start = int_token.cur;
	return (r);
}
