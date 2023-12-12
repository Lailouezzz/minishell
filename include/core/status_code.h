/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status_code.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-boud <ale-boud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 01:39:12 by ale-boud          #+#    #+#             */
/*   Updated: 2023/12/12 02:14:01 by ale-boud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file status_code.h
 * @author ale-boud (ale-boud@student.42.fr)
 * @brief Definition of minishell error code.
 * @date 2023-12-12
 * @copyright Copyright (c) 2023
 */

#ifndef STATUS_CODE_H
# define STATUS_CODE_H

// ************************************************************************** //
// *                                                                        * //
// * Status code.                                                           * //
// *                                                                        * //
// ************************************************************************** //

# define MS_OK 0
# define MS_FAILURE 1
# define MS_BUILTIN_BAD_USAGE 2
# define MS_PERM_DENIED 126
# define MS_COMMAND_NOT_FOUND 127

#endif
