/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-boud <ale-boud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 14:12:05 by ale-boud          #+#    #+#             */
/*   Updated: 2023/12/14 03:12:33 by ale-boud         ###   ########.fr       */
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

# include "tokenizer/lr_token_list.h"
# include "utils/dyn_str.h"
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
typedef struct s_int_token
{
	/**
	 * @brief Where we are ?
	 */
	const char		*cur;

	/**
	 * @brief The current word read.
	 */
	t_dyn_str		word_read;
}	t_int_token;

// ************************************************************************** //
// *                                                                        * //
// * Function prototypes.                                                   * //
// *                                                                        * //
// ************************************************************************** //

/**
 * @brief 
 * @param lrtoks Store the @s_lr_token_list read.
 * @param start Pointer to a char in a null-terminated string.
 * 		After the call this pointer is placed at the end of the read token.
 * @return int 0 on success. non-null value on error.
 */
int		tokenize(
			t_lr_token_list *lrtoks,
			const char **start
			);

// ************************************************************************** //
// *                                                                        * //
// * Token free callback table definition.                                  * //
// *                                                                        * //
// ************************************************************************** //

/**
 * @brief Token free callback table.
 */
extern const t_lr_token_free_cb	g_tok_free_cbs[TOKEN__COUNT];

// ************************************************************************** //
// *                                                                        * //
// * Token generator prototypes.                                            * //
// *                                                                        * //
// ************************************************************************** //

/**
 * @brief Generate a TOKEN_WORD
 * @param lrtok Store the @s_lr_token generated.
 * @param str The word string.
 * @return int 0 on success. non-null value on error.
 */
int		_token_gen_word(
			t_lr_token *lrtok,
			char *str
			);

/**
 * @brief Generate a TOKEN_IO
 * @param lrtok Store the @s_lr_token generated.
 * @param type The @s_io_type.
 * @return int 0 on success. non-null value on error.
 */
int		_token_gen_io(
			t_lr_token *lrtok,
			t_io_type type
			);

/**
 * @brief Generate a TOKEN_AND_OR
 * @param lrtok Store the @s_lr_token generated.
 * @param int_token The @s_logic_type.
 * @return int 0 on success. non-null value on error.
 */
int		_token_gen_and_or(
			t_lr_token *lrtok,
			t_logic_type type
			);

/**
 * @brief Generate a TOKEN_PIPE
 * @param lrtok Store the @s_lr_token generated.
 * @param int_token The @s_int_token.
 * @return int 0 on success. non-null value on error.
 */
int		_token_gen_pipe(
			t_lr_token *lrtok
			);

/**
 * @brief Generate a TOKEN_OBRACKET
 * @param lrtok Store the @s_lr_token generated.
 * @param int_token The @s_int_token.
 * @return int 0 on success. non-null value on error.
 */
int		_token_gen_obracket(
			t_lr_token *lrtok
			);

/**
 * @brief Generate a TOKEN_CBRACKET
 * @param lrtok Store the @s_lr_token generated.
 * @param int_token The @s_int_token.
 * @return int 0 on success. non-null value on error.
 */
int		_token_gen_cbracket(
			t_lr_token *lrtok
			);

/**
 * @brief Generate a TOKEN_END
 * @param lrtok Store the @s_lr_token generated.
 * @return int 0 on success. non-null value on error.
 */
int		_token_gen_end(
			t_lr_token *lrtok
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

#endif
