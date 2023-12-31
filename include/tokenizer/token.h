/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-boud <ale-boud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 00:11:00 by ale-boud          #+#    #+#             */
/*   Updated: 2023/12/14 02:42:59 by ale-boud         ###   ########.fr       */
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
typedef enum e_io_type
{
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
 * @enum e_logic_type
 * @brief The logic type.
 */
typedef enum e_logic_type
{
	/** @brief Logic AND "&&" */
	LOGIC_AND,
	/** @brief Logic OR "||" */
	LOGIC_OR,
	/** @brief No logic operator */
	LOGIC_NONE,
	LOGIC__COUNT,
}	t_logic_type;

/**
 * @enum e_token_type
 * @brief The token (lexeme type).
 */
typedef enum e_token_type
{
	/** @brief Describe a word. (this is literally a sting) */
	TOKEN_WORD,
	/** @brief Describe a redirection mode. {"<", "<<", ">>", ">"} */
	TOKEN_IO,
	/** @brief Describe a logic operation. {"&&", "||"} */
	TOKEN_AND_OR,
	/** @brief Describe a pipe '|' */
	TOKEN_PIPE,
	/** @brief Open bracket '(' */
	TOKEN_OBRACKET,
	/** @brief Close bracket ')' */
	TOKEN_CBRACKET,
	/** @brief Describe the end */
	TOKEN_END,
	TOKEN__COUNT,
}	t_token_type;

#endif
