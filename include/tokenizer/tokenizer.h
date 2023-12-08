/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-boud <ale-boud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 14:12:05 by ale-boud          #+#    #+#             */
/*   Updated: 2023/12/08 16:13:34 by ale-boud         ###   ########.fr       */
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

/**
 * @struct s_int_token
 * @brief Define the intermediate token.
 */
typedef struct s_int_token {
	/**
	 * @brief Where we start ?
	 */
	const char		*start;

	/**
	 * @brief The length of the token (number of chars).
	 */
	size_t			len;
}	t_int_token;

/**
 * @brief Token generation callback.
 */
typedef int						(*t_token_gen_cb)(t_lr_token *lrtok,
	const t_int_token *int_token);

// ************************************************************************** //
// *                                                                        * //
// * Token generator callback table definition.                             * //
// *                                                                        * //
// ************************************************************************** //

/**
 * @brief Token generator callback table.
 */
extern const t_token_gen_cb		g_tok_gen_cbs[TOKEN__COUNT];

/**
 * @brief Token free callback table.
 */
extern const t_lr_token_free_cb	g_tok_free_cbs[TOKEN__COUNT];

// ************************************************************************** //
// *                                                                        * //
// * Token generator callbacks prototypes.                                  * //
// *                                                                        * //
// ************************************************************************** //

/**
 * @brief Generator a TOKEN_WORD
 * @param lrtok Store the @s_lr_token generated.
 * @param int_token The @s_int_token.
 * @return int 0 on success. non-null value on error.
 */
int		_token_gen_word_cb(
			t_lr_token *lrtok,
			const t_int_token *int_token
			);

/**
 * @brief Generator a TOKEN_IO
 * @param lrtok Store the @s_lr_token generated.
 * @param int_token The @s_int_token.
 * @return int 0 on success. non-null value on error.
 */
int		_token_gen_io_cb(
			t_lr_token *lrtok,
			const t_int_token *int_token
			);

/**
 * @brief Generator a TOKEN_END
 * @param lrtok Store the @s_lr_token generated.
 * @param int_token The @s_int_token.
 * @return int 0 on success. non-null value on error.
 */
int		_token_gen_end_cb(
			t_lr_token *lrtok,
			const t_int_token *int_token
			);

// ************************************************************************** //
// *                                                                        * //
// * Token free callbacks prototypes.                                       * //
// *                                                                        * //
// ************************************************************************** //

/**
 * @brief Word free callback.
 * @param data The data to free.
 */
void	_token_free_word_cb(
			t_lr_token_type *data
			);

// ************************************************************************** //
// *                                                                        * //
// * Function prototypes.                                                   * //
// *                                                                        * //
// ************************************************************************** //

/**
 * @brief 
 * @param lrtok Store the @s_lr_token read.
 * @param start Pointer to a char in a null-terminated string.
 * 		After the call this pointer is placed at the end of the read token.
 * @return int 0 on success. non-null value on error.
 */
int		tokenize(
			t_lr_token *lrtok,
			const char **start
			);

#endif
