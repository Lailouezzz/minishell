/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-boud <ale-boud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 08:02:47 by ale-boud          #+#    #+#             */
/*   Updated: 2023/12/01 21:50:32 by ale-boud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file ast.h
 * @author ale-boud (ale-boud@student.42.fr)
 * @brief The AST definition.
 * @date 2023-11-29
 * @copyright Copyright (c) 2023
 */

#ifndef AST_H
# define AST_H

// ************************************************************************** //
// *                                                                        * //
// * Includes                                                               * //
// *                                                                        * //
// ************************************************************************** //

# include <stdlib.h>

# include "tokenizer/token.h"

// ************************************************************************** //
// *                                                                        * //
// * Structure definitions.                                                 * //
// *                                                                        * //
// ************************************************************************** //

typedef char	*t_progname;

typedef char	**t_args;

typedef struct s_io_info {
	t_io_type	type;
	char		*file;
}	t_io_info;

typedef struct s_command_io {
	t_io_info	**io_infos;
	size_t		alloced;
	size_t		used;
}	t_command_io;

typedef struct s_command {
	t_progname		pn;
	t_args			args;
	t_command_io	*cio;
}	t_command;

// ************************************************************************** //
// *                                                                        * //
// * Function definition.                                                   * //
// *                                                                        * //
// ************************************************************************** //

t_args			args_create(
					char *str
					);

t_args			args_append(
					t_args args,
					char *str
					);

void			args_destroy(
					t_args args
					);

t_io_info		*io_info_create(
					t_io_type type,
					char *str
					);

void			io_info_destroy(
					t_io_info *io_info
					);

t_command_io	*cio_create(
					t_io_info *io_info
					);

int				cio_append(
					t_command_io *cio,
					t_io_info *io_info
					);

void			cio_destroy(
					t_command_io *cio
					);

t_command		*command_create(
					t_progname pn
					);

t_command		*command_create_args(
					t_progname pn,
					t_args args
					);

int				command_add_io(
					t_command *command,
					t_command_io *cio
					);

void			command_destroy(
					t_command *command
					);

#endif
