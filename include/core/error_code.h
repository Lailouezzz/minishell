/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_code.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-boud <ale-boud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 01:59:57 by ale-boud          #+#    #+#             */
/*   Updated: 2023/12/12 02:00:22 by ale-boud         ###   ########.fr       */
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

# define ERR_OK 0
# define ERR_NOT_VALID_IDENTIFIER 1
# define ERR_BAD_ALLOC 2
# define ERR_COMMAND_NOT_FOUND 3
# define ERR_PERM_DENIED 4
# define ERR_FATAL 5

#endif
