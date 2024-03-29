/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_info.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amassias <amassias@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 20:11:32 by ale-boud          #+#    #+#             */
/*   Updated: 2024/03/12 18:35:19 by amassias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file io_info.c
 * @author ale-boud (ale-boud@student.42.fr)
 * @brief AST io info function implementation.
 * @date 2023-12-11
 * @copyright Copyright (c) 2023
 */

// ************************************************************************** //
// *                                                                        * //
// * Includes.                                                              * //
// *                                                                        * //
// ************************************************************************** //

#include "parser/ast.h"

// ************************************************************************** //
// *                                                                        * //
// * Header function.                                                       * //
// *                                                                        * //
// ************************************************************************** //

t_io_info	*io_info_create(
				t_io_type type,
				char *file
				)
{
	t_io_info	*io_info;

	io_info = malloc(sizeof(*io_info));
	if (io_info == NULL)
		return (NULL);
	io_info->io_type = type;
	io_info->file = file;
	io_info->fd = -1;
	return (io_info);
}

void	io_info_destroy(
			t_io_info *io_info
			)
{
	if (io_info != NULL)
	{
		io_info_free(io_info);
		free(io_info);
	}
}

void	io_info_free(
			t_io_info *io_info
			)
{
	if (io_info != NULL)
	{
		if (io_info->file != NULL)
			free(io_info->file);
	}
}
