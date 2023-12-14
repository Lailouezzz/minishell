/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_code.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-boud <ale-boud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 01:59:57 by ale-boud          #+#    #+#             */
/*   Updated: 2023/12/14 03:17:48 by ale-boud         ###   ########.fr       */
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
	ERR_OK,
	ERR_NOT_VALID_IDENTIFIER,
	ERR_BAD_ALLOC,
	ERR_COMMAND_NOT_FOUND,
	ERR_PERM_DENIED,
	ERR_FATAL,
	ERR_UNCLOSED_QUOTE,
}	t_ms_error;

#endif
