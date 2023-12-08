/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-boud <ale-boud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 08:02:47 by ale-boud          #+#    #+#             */
/*   Updated: 2023/12/08 16:36:40 by ale-boud         ###   ########.fr       */
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

/**
 * @brief The program name (or path).
 */
typedef char	*t_progname;

/**
 * @brief The args.
 */
typedef char	**t_args;

/**
 * @struct s_io_info
 * @brief The representation of an IO information (IO mode, and file path).
 */
typedef struct s_io_info
{
	/**
	 * @brief The IO type.
	 */
	t_io_type	type;

	/**
	 * @brief The file path.
	 */
	char		*file;
}	t_io_info;

/**
 * @struct s_command_io
 * @brief The list of redirection.
 */
typedef struct s_command_io
{
	/**
	 * @brief A table of pointers to #s_io_info.
	 */
	t_io_info	**io_infos;

	/**
	 * @brief The alloced space of #io_infos.
	 */
	size_t		alloced;

	/**
	 * @brief The space of #io_infos used.
	 */
	size_t		used;
}	t_command_io;

/**
 * @struct s_command
 * @brief The representation of a command.
 */
typedef struct s_command
{
	/**
	 * @brief The #t_progname.
	 */
	t_progname		pn;

	/**
	 * @brief The #t_args.
	 */
	t_args			args;

	/**
	 * @brief The #s_command_io.
	 */
	t_command_io	*cio;
}	t_command;

// ************************************************************************** //
// *                                                                        * //
// * Function definition.                                                   * //
// *                                                                        * //
// ************************************************************************** //

/**
 * @brief Create an args list (#t_args).
 * @param str The argument.
 * @return t_args The #t_args.
 */
t_args			args_create(
					char *str
					);

/**
 * @brief Append an argument to an args list (#t_args).
 * @param args The #t_args.
 * @param str The argument to append.
 * @return t_args The #t_args.
 */
t_args			args_append(
					t_args args,
					char *str
					);

/**
 * @brief Free #t_args.
 * @param args #t_args to free.
 */
void			args_destroy(
					t_args args
					);

/**
 * @brief Create an #s_io_info.
 * @param type The #e_io_type of the io redirection.
 * @param str The filename (or path).
 * @return t_io_info* 
 */
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
