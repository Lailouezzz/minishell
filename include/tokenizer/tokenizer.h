/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-boud <ale-boud@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 14:12:05 by ale-boud          #+#    #+#             */
/*   Updated: 2023/11/30 17:14:03 by ale-boud         ###   ########.fr       */
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
	const char		*start;
	size_t			len;
}	t_int_token;

typedef int		(*t_token_gen_cb)(t_lr_token *lrtok, const t_int_token *int_token);
typedef void	(*t_token_free_cb)(void *data);

typedef struct s_token_list {
	t_lr_token	*lrtoks;
	size_t		alloced;
	size_t		used;
}	t_token_list;

// ************************************************************************** //
// *                                                                        * //
// * Token generator callback table definition.                             * //
// *                                                                        * //
// ************************************************************************** //

extern const t_token_gen_cb	g_tok_gen_cbs[TOKEN__COUNT];
extern const t_token_free_cb	g_tok_free_cbs[TOKEN__COUNT];

// ************************************************************************** //
// *                                                                        * //
// * Token generator callbacks prototypes.                                  * //
// *                                                                        * //
// ************************************************************************** //

int				_token_gen_word_cb(
					t_lr_token *lrtok,
					const t_int_token *int_token
					);

int				_token_gen_io_cb(
					t_lr_token *lrtok,
					const t_int_token *int_token
					);

int				_token_gen_end_cb(
					t_lr_token *lrtok,
					const t_int_token *int_token
					);

// ************************************************************************** //
// *                                                                        * //
// * Function prototypes.                                                   * //
// *                                                                        * //
// ************************************************************************** //

t_token_list	*tokenizer(
					const char *str
					);

int				tokenize(
					t_lr_token *lrtok,
					const char **start
					);

void			token_list_destoy(
					t_token_list *lrtoks
					);

#endif
