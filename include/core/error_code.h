/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_code.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-boud <ale-boud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 01:59:57 by ale-boud          #+#    #+#             */
/*   Updated: 2024/03/11 15:22:07 by ale-boud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file error_code.h
 * @author ale-boud (ale-boud@student.42.fr)
 * @brief All the minishell error code.
 * @date 2023-12-12
 * @copyright Copyright (c) 2023
 */

#ifndef ERROR_CODE_H
# define ERROR_CODE_H

// ************************************************************************** //
// *                                                                        * //
// * Error code.                                                            * //
// *                                                                        * //
// ************************************************************************** //

typedef enum s_ms_error
{
	MS_OK,
	MS_NOT_VALID_IDENTIFIER,
	MS_SYNTAX_ERROR,
	MS_BAD_ALLOC,
	MS_EMPTY_COMMAND,
	MS_COMMAND_NOT_FOUND,
	MS_COMMAND_IS_DIRECTORY,
	MS_PERM_DENIED,
	MS_FATAL,
	MS_UNCLOSED_QUOTE,
}	t_ms_error;

#endif
