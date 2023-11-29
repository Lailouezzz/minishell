/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-boud <ale-boud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 08:25:01 by ale-boud          #+#    #+#             */
/*   Updated: 2023/11/29 11:38:25 by ale-boud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file ast.c
 * @author ale-boud (ale-boud@student.42.fr)
 * @brief The AST helpers.
 * @date 2023-11-29
 * @copyright Copyright (c) 2023
 */

// ************************************************************************** //
// *                                                                        * //
// * Includes.                                                              * //
// *                                                                        * //
// ************************************************************************** //

#include <stdlib.h>

#include "ast.h"

#include "utils.h"

// ************************************************************************** //
// *                                                                        * //
// * Helper function definition.                                            * //
// *                                                                        * //
// ************************************************************************** //

static void	_strs_free(
				char **str
				);

// ************************************************************************** //
// *                                                                        * //
// * Header functions.                                                      * //
// *                                                                        * //
// ************************************************************************** //

t_args	args_create(
			const char *str
			)
{
	t_args	args;

	args = malloc(sizeof(*args) * 2);
	if (args == NULL)
		return (NULL);
	args[1] = NULL;
	args[0] = ft_strdup(str);
	if (args[0] == NULL)
	{
		free(args);
		return (NULL);
	}
	return (args);
}

t_args	args_append(
			t_args args,
			const char *str
			)
{
	size_t	k;
	t_args	nargs;

	k = 0;
	while (args[k] != NULL)
		++k;
	nargs = malloc((k + 2) * sizeof(nargs));
	if (nargs == NULL)
	{
		_strs_free(args);
		return (NULL);
	}
	ft_memcpy(nargs + 1, args, k * sizeof(*nargs));
	nargs[0] = ft_strdup(str);
	if (nargs[0] == NULL)
	{
		_strs_free(args);
		free(nargs);
		return (NULL);
	}
	nargs[k + 1] = NULL;
	free(args);
	return (nargs);
}

void	args_destroy(
			t_args args
			)
{
	_strs_free(args);
	free(args);
}

t_io_info	*io_info_create(
				t_io_type type,
				const char *str
				)
{
	t_io_info	*io_info;

	io_info = malloc(sizeof(*io_info));
	if (io_info == NULL)
		return (NULL);
	io_info->type = type;
	io_info->file = ft_strdup(str);
	if (io_info->file == NULL)
	{
		free(io_info);
		return (NULL);
	}
	return (io_info);
}

void	io_info_destroy(
			t_io_info *io_info
			)
{
	if (io_info->file != NULL)
		free(io_info->file);
	free(io_info);
}

t_command_io	*cio_create(
					t_io_info *io_info
					)
{
	t_command_io	*cio;

	cio = malloc(sizeof(*cio));
	if (cio == NULL)
		return (NULL);
	cio->alloced = 1;
	cio->used = 1;
	cio->io_infos = malloc(sizeof(*cio->io_infos));
	if (cio->io_infos == NULL)
	{
		free(cio);
		return (NULL);
	}
	cio->io_infos[0] = io_info;
	return (cio);
}

int	cio_append(
		t_command_io *cio,
		t_io_info *io_info
		)
{
	if (cio->used >= cio->alloced)
	{
		cio->io_infos = ft_realloc(cio->io_infos,
				cio->alloced * sizeof(*cio->io_infos),
				(cio->alloced + 1) * sizeof(*cio->io_infos));
		++cio->alloced;
		if (cio->io_infos == NULL)
		{
			free(cio);
			return (1);
		}
	}
	cio->io_infos[cio->used++] = io_info;
	return (0);
}

void	cio_destroy(
			t_command_io *cio
			)
{
	size_t	k;

	k = 0;
	if (cio->io_infos != NULL)
	{
		while (k < cio->used)
		{
			io_info_destroy(cio->io_infos[k]);
			++k;
		}
		free(cio->io_infos);
	}
	free(cio);
}

t_command	*command_create(
				t_progname pn
				)
{
	t_command	*command;

	command = malloc(sizeof(*command));
	if (command == NULL)
		return (NULL);
	command->cio = NULL;
	command->pn = pn;
	command->args = malloc(sizeof(t_args));
	if (command->args == NULL)
	{
		free(command);
		return (NULL);
	}
	command->args[0] = NULL;
	return (command);
}

t_command	*command_create_args(
				t_progname pn,
				t_args args
				)
{
	t_command	*command;

	command = command_create(pn);
	if (command == NULL)
		return (NULL);
	_strs_free(command->args);
	free(command->args);
	command->args = args;
	return (command);
}

int	command_add_io(
		t_command *command,
		t_command_io *cio
		)
{
	command->cio = cio;
	return (0);
}

void	command_destroy(
			t_command *command
			)
{
	if (command->cio != NULL)
		cio_destroy(command->cio);
	if (command->args != NULL)
		args_destroy(command->args);
	if (command->pn != NULL)
		free(command->pn);
	free(command);
}

// ************************************************************************** //
// *                                                                        * //
// * Helper function implementation.                                        * //
// *                                                                        * //
// ************************************************************************** //

static void	_strs_free(
				char **str
				)
{
	while (*str != NULL)
		free(*(str++));
}
