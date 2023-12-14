/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status_code.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-boud <ale-boud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 01:39:12 by ale-boud          #+#    #+#             */
/*   Updated: 2023/12/14 03:02:51 by ale-boud         ###   ########.fr       */
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

typedef enum s_ms_status
{
	MS_OK,
	MS_FAILURE,
	MS_BUILTIN_BAD_USAGE,
	MS_PERM_DENIED,
	MS_COMMAND_NOT_FOUND,
}	t_ms_status;

#endif
