/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amassias <amassias@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 01:15:15 by ale-boud          #+#    #+#             */
/*   Updated: 2024/03/05 22:31:54 by amassias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file exec.h
 * @author ale-boud (ale-boud@student.42.fr)
 * @brief The executor definiton.
 * @date 2023-12-12
 * @copyright Copyright (c) 2023
 */

#ifndef EXEC_H
# define EXEC_H

// ************************************************************************** //
// *                                                                        * //
// * Includes.                                                              * //
// *                                                                        * //
// ************************************************************************** //

# include <stdnoreturn.h>

# include <lr_parser.h>

# include "core/env.h"
# include "parser/ast.h"
# include "tokenizer/lr_token_list.h"

// ************************************************************************** //
// *                                                                        * //
// * Structure definition.                                                  * //
// *                                                                        * //
// ************************************************************************** //

typedef enum e_file_status
{
	FILE_STATUS_OK,
	FILE_STATUS_NOT_FOUND,
	FILE_STATUS_DIRECTORY,
	FILE_STATUS_PERM_DENIED
}	t_file_status;

typedef struct s_exec_unit
{
	int		out_fd;
	int		in_fd;
	char	**args;
	char	*path;
	int		is_builtin;
}	t_exec_unit;

typedef struct s_exec_ctx
{
	t_env_ctx		*env_ctx;
	t_lr_parser_ctx	*parser_ctx;
	t_command_line	*current_cl;
	char			*current_line;
}	t_exec_ctx;

// ************************************************************************** //
// *                                                                        * //
// * Function definition.                                                   * //
// *                                                                        * //
// ************************************************************************** //

void			exec_init(
					t_exec_ctx *ctx,
					t_env_ctx *env_ctx,
					t_lr_parser_ctx *parser_ctx
					);

t_ms_error		exec_exec(
					t_exec_ctx *ctx,
					const t_command_line *cl
					);

void			exec_loop(
					t_exec_ctx *ctx
					);

noreturn void	exec_cleanup_exit(
					t_exec_ctx *ctx,
					t_ms_status code
					);

// ************************************************************************** //
// *                                                                        * //
// * Signal handler.                                                        * //
// *                                                                        * //
// ************************************************************************** //

void			exec_set_interactive(void);

void			exec_set_in_execution(void);

#endif
