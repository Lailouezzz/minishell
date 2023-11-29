/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-boud <ale-boud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 00:11:00 by ale-boud          #+#    #+#             */
/*   Updated: 2023/11/29 14:20:39 by ale-boud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file token.h
 * @author ale-boud (ale-boud@student.42.fr)
 * @brief The token definition.
 * @date 2023-11-29
 * @copyright Copyright (c) 2023
 */

#ifndef TOKEN_H
# define TOKEN_H

// ************************************************************************** //
// *                                                                        * //
// * Structure definition.                                                  * //
// *                                                                        * //
// ************************************************************************** //

/**
 * @enum e_io_type
 * @brief The redirection io type.
 */
typedef enum e_io_type {
	/** @brief Redirect input "<" */
	IO_IN,

	/** @brief Redirect input with an heredoc "<<" */
	IO_HEREDOC,

	/** @brief Redirect output ">" */
	IO_OUT,

	/** @brief Redirect output in append mode ">>" */
	IO_APPEND,

	IO__COUNT,
}	t_io_type;

/**
 * @enum e_token_type
 * @brief The token (lexeme type).
 */
typedef enum e_token_type {
	/** @brief Describe a word. (this is literally a sting) */
	TOKEN_WORD,

	/** @brief Describe a redirection mode. {"<", "<<", ">>", ">"} */
	TOKEN_IO,

	/** @brief Describe the end */
	TOKEN_END,

	TOKEN__COUNT,
}	t_token_type;

/**
 * @union u_token_data
 * @brief The data of token.
 */
typedef union u_token_data {
	/** @brief TOKEN_WORD */
	char		*word;

	/** @brief TOKEN_IO */
	t_io_type	io_type;
}	t_token_data;

#endif
