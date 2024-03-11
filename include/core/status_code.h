/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status_code.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amassias <amassias@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 01:39:12 by ale-boud          #+#    #+#             */
/*   Updated: 2024/03/11 18:42:49 by amassias         ###   ########.fr       */
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
	MS_STATUS_OK=0,
	MS_STATUS_FAILURE=1,
	MS_STATUS_BUILTIN_BAD_USAGE=2,
	MS_STATUS_PERM_DENIED=126,
	MS_STATUS_COMMAND_NOT_FOUND=127,
	MS_STATUS_SIGINT=130,
	MS_STATUS_SIGQUIT=131,
}	t_ms_status;

#endif
