/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-boud <ale-boud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 08:02:47 by ale-boud          #+#    #+#             */
/*   Updated: 2023/12/11 22:57:48 by ale-boud         ###   ########.fr       */
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
 * @brief The argument.
 */
typedef struct s_args
{
	char	**args;
	size_t	alloced;
	size_t	used;
}	t_args;

typedef struct s_io_info
{
	t_io_type	io_type;
	char		*file;
}	t_io_info;

typedef struct s_redirect_list
{
	t_io_info	*io_infos;
	size_t		alloced;
	size_t		used;
}	t_redirect_list;

typedef enum e_arg_red_type
{
	AR_ARG,
	AR_REDIRECT,
	AR__COUNT,
}	t_arg_red_type;

typedef union u_arg_red_data
{
	char		*arg;
	t_io_info	*io_info;
}	t_arg_red_data;

typedef struct s_arg_red
{
	t_arg_red_type	type;
	t_arg_red_data	data;
}	t_arg_red;

typedef struct s_args_redirect_list
{
	t_redirect_list	*redirect_list;
	t_args			*args;
}	t_args_redirect_list;

typedef struct s_simple_command
{
	t_redirect_list	*redirect_list;
	t_args			*args;
	t_progname		pn;
}	t_simple_command;

typedef enum e_command_type
{
	COMMAND_SIMPLE_COMMAND,
	COMMAND_SUBSHELL,
	COMMAND__COUNT,
}	t_command_type;

typedef struct s_command
{
	t_command_type	type;
	void			*command;
}	t_command;

typedef struct s_pipeline
{
	t_command	*commands;
	size_t		alloced;
	size_t		used;
}	t_pipeline;

typedef struct s_and_or
{
	t_pipeline		*right_pipeline;
	t_logic_type	logic_type;
	struct s_and_or	*left;
}	t_and_or;

typedef struct s_subshell
{
	t_and_or		*and_or;
	t_redirect_list	*redirect_list;
}	t_subshell;

typedef struct s_command_line
{
	t_and_or	*and_or;
}	t_command_line;

// ************************************************************************** //
// *                                                                        * //
// * Command line function.                                                 * //
// *                                                                        * //
// ************************************************************************** //

t_command_line			*command_line_create(
							t_and_or *and_or
							);

void					command_line_destroy(
							t_command_line *cl
							);

// ************************************************************************** //
// *                                                                        * //
// * And or function                                                        * //
// *                                                                        * //
// ************************************************************************** //

t_and_or				*and_or_leaf(
							t_pipeline *pl
							);

t_and_or				*and_or_node(
							t_and_or *left,
							t_logic_type type,
							t_pipeline *pl
							);

void					and_or_destroy(
							t_and_or *and_or
							);

// ************************************************************************** //
// *                                                                        * //
// * Command function.                                                      * //
// *                                                                        * //
// ************************************************************************** //

t_command				*command_create(
							void *commandp,
							t_command_type type
							);

void					command_destroy(
							t_command *command
							);

void					command_free(
							t_command *command
							);

// ************************************************************************** //
// *                                                                        * //
// * Pipeline function.                                                     * //
// *                                                                        * //
// ************************************************************************** //

t_pipeline				*pipeline_create(
							t_command *command
							);

int						pipeline_pushback(
							t_pipeline *pl,
							t_command *command
							);

void					pipeline_destroy(
							t_pipeline *pl
							);

// ************************************************************************** //
// *                                                                        * //
// * Simple command function.                                               * //
// *                                                                        * //
// ************************************************************************** //

t_simple_command		*simple_command_create(
							t_progname pn
							);

int						simple_command_add_rl(
							t_simple_command *sc,
							t_redirect_list *rl
							);

/**
 * @brief Add the args redirect list to the simple command.
 * 		/!\ CALL AFTER ADD RL. /!\
 * @param sc The #s_simple_command.
 * @param arl The #s_args_redirect_list.
 * @return int 0 on success. non-null value if error.
 */
int						simple_command_add_arl(
							t_simple_command *sc,
							t_args_redirect_list *arl
							);

void					simple_command_destroy(
							t_simple_command *sc
							);

// ************************************************************************** //
// *                                                                        * //
// * Subshell function.                                                     * //
// *                                                                        * //
// ************************************************************************** //

t_subshell				*subshell_create(
							t_and_or *and_or
							);

int						subshell_add_rl(
							t_subshell *ss,
							t_redirect_list *rl
							);

void					subshell_destroy(
							t_subshell *ss
							);

// ************************************************************************** //
// *                                                                        * //
// * Redirect list function.                                                * //
// *                                                                        * //
// ************************************************************************** //

t_redirect_list			*redirect_list_create(
							t_io_info *io_info
							);

t_redirect_list			*redirect_list_init(void);

int						redirect_list_pushback(
							t_redirect_list *rl,
							t_io_info *io_info
							);

int						redirect_list_cat(
							t_redirect_list *rl1,
							t_redirect_list *rl2
							);

void					redirect_list_destroy(
							t_redirect_list *rl
							);

// ************************************************************************** //
// *                                                                        * //
// * Arg red function.                                                      * //
// *                                                                        * //
// ************************************************************************** //

t_arg_red				*arg_red_create_arg(
							char *arg
							);

t_arg_red				*arg_red_create_redirect(
							t_io_info *io_info
							);

void					arg_red_destroy(
							t_arg_red *ar
							);

// ************************************************************************** //
// *                                                                        * //
// * Args redirect list function.                                           * //
// *                                                                        * //
// ************************************************************************** //

t_args_redirect_list	*args_redirect_list_init(void);

t_args_redirect_list	*args_redirect_list_create(
							t_arg_red *ar
							);

int						args_redirect_list_pusback(
							t_args_redirect_list *arl,
							t_arg_red *ar
							);

void					args_redirect_list_destroy(
							t_args_redirect_list *arl
							);

// ************************************************************************** //
// *                                                                        * //
// * Args function.                                                         * //
// *                                                                        * //
// ************************************************************************** //

t_args					*args_init(void);

t_args					*args_create(
							char *arg
							);

int						args_pushback(
							t_args *args,
							char *arg
							);

int						args_cat(
							t_args *args1,
							t_args *args2
							);

void					args_destroy(
							t_args *args
							);

// ************************************************************************** //
// *                                                                        * //
// * IO info function.                                                      * //
// *                                                                        * //
// ************************************************************************** //

t_io_info				*io_info_create(
							t_io_type type,
							char *file
							);

void					io_info_destroy(
							t_io_info *io_info
							);

void					io_info_free(
							t_io_info *io_info
							);

#endif
