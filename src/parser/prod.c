/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prod.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-boud <ale-boud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 22:32:35 by ale-boud          #+#    #+#             */
/*   Updated: 2023/12/11 23:04:31 by ale-boud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file prod.c
 * @author ale-boud (ale-boud@student.42.fr)
 * @brief The prod implementation.
 * @date 2023-11-29
 * @copyright Copyright (c) 2023
 */

// ************************************************************************** //
// *                                                                        * //
// * Includes.                                                              * //
// *                                                                        * //
// ************************************************************************** //

#include "parser/ast.h"
#include "parser/prod.h"

#include "utils.h"

// ************************************************************************** //
// *                                                                        * //
// * The production callbacks.                                              * //
// *                                                                        * //
// ************************************************************************** //

const t_lr_prod_cb	g_prod_cbs[PROD__COUNT] = {
[PROD_SIMPLE_COMMAND__RLPN] = {_prod_simple_command__rlpn, 2,
	_free_simple_command__rlpn},
[PROD_SIMPLE_COMMAND__1] = {_prod_simple_command__1, 1,
	_free_simple_command__1},
[PROD_SIMPLE_COMMAND__PNARL] = {_prod_simple_command__pnarl, 2,
	_free_simple_command__pnarl},
[PROD_SIMPLE_COMMAND__3] = {_prod_simple_command__3, 3,
	_free_simple_command__3},
[PROD_COMMAND_LINE] = {_prod_command_line, 1, _free_command_line},
[PROD_COMMAND__SS1] = {_prod_command__ss1, 1, _free_command__ss1},
[PROD_COMMAND__SS2] = {_prod_command__ss2, 2, _free_command__ss2},
[PROD_COMMAND__SC] = {_prod_command__sc, 1, _free_command__sc},
[PROD_SUBSHELL] = {_prod_subshell, 3, _free_subshell},
[PROD_AND_OR__1] = {_prod_and_or__1, 1, _free_and_or__1},
[PROD_AND_OR__3] = {_prod_and_or__3, 3, _free_and_or__3},
[PROD_PIPELINE__1] = {_prod_pipeline__1, 1, _free_pipeline__1},
[PROD_PIPELINE__3] = {_prod_pipeline__3, 3, _free_pipeline__3},
[PROD_IO_INFO] = {_prod_io_info, 2, _free_io_info},
[PROD_PROGNAME] = {_prod_progname, 1, _free_progname},
[PROD_ARG_RED__ARG] = {_prod_arg_red__arg, 1, _free_arg_red__arg},
[PROD_ARG_RED__IO] = {_prod_arg_red__io, 1, _free_arg_red__io},
[PROD_ARG_RED_LIST__1] = {_prod_arg_red_list__1, 1, _free_arg_red_list__1},
[PROD_ARG_RED_LIST__2] = {_prod_arg_red_list__2, 2, _free_arg_red_list__2},
[PROD_REDIRECT_LIST__1] = {_prod_redirect_list__1, 1, _free_redirect_list__1},
[PROD_REDIRECT_LIST__2] = {_prod_redirect_list__2, 2, _free_redirect_list__2},
};

// ************************************************************************** //
// *                                                                        * //
// * Callback functions.                                                    * //
// *                                                                        * //
// ************************************************************************** //

void	*_prod_simple_command__rlpn(
			t_lr_stack_item *item,
			void *usrptr
			)
{
	t_redirect_list *const	rl = item[0].data.derived.data;
	t_progname const		pn = item[1].data.derived.data;
	t_simple_command		*sc;

	(void)(usrptr);
	sc = simple_command_create(pn);
	if (sc == NULL)
		return (redirect_list_destroy(rl), NULL);
	if (simple_command_add_rl(sc, rl))
		return (NULL);
	return (sc);
}

void	_free_simple_command__rlpn(
			void *to_free,
			void *usrptr
			)
{
	(void)(usrptr);
	simple_command_destroy(to_free);
}

void	*_prod_simple_command__1(
			t_lr_stack_item *item,
			void *usrptr
			)
{
	t_progname const	pn = item[0].data.derived.data;

	(void)(usrptr);
	return (simple_command_create(pn));
}

void	_free_simple_command__1(
			void *to_free,
			void *usrptr
			)
{
	(void)(usrptr);
	simple_command_destroy(to_free);
}

void	*_prod_simple_command__pnarl(
			t_lr_stack_item *item,
			void *usrptr
			)
{
	t_progname const			pn = item[0].data.derived.data;
	t_args_redirect_list *const	arl = item[1].data.derived.data;
	t_simple_command		*sc;

	(void)(usrptr);
	sc = simple_command_create(pn);
	if (sc == NULL)
		return (args_redirect_list_destroy(arl), NULL);
	if (simple_command_add_arl(sc, arl))
		return (NULL);
	return (sc);
}

void	_free_simple_command__pnarl(
			void *to_free,
			void *usrptr
			)
{
	(void)(usrptr);
	simple_command_destroy(to_free);
}

void	*_prod_simple_command__3(
			t_lr_stack_item *item,
			void *usrptr
			)
{
	t_redirect_list *const		rl = item[0].data.derived.data;
	t_progname const			pn = item[1].data.derived.data;
	t_args_redirect_list *const	arl = item[2].data.derived.data;
	t_simple_command		*sc;

	(void)(usrptr);
	sc = simple_command_create(pn);
	if (sc == NULL)
		return (args_redirect_list_destroy(arl),
			redirect_list_destroy(rl), NULL);
	if (simple_command_add_rl(sc, rl))
		return (args_redirect_list_destroy(arl), NULL);
	if (simple_command_add_arl(sc, arl))
		return (NULL);
	return (sc);
}

void	_free_simple_command__3(
			void *to_free,
			void *usrptr
			)
{
	(void)(usrptr);
	simple_command_destroy(to_free);
}

void	*_prod_command_line(
			t_lr_stack_item *item,
			void *usrptr
			)
{
	t_and_or *const	and_or = item[0].data.derived.data;

	(void)(usrptr);
	return (command_line_create(and_or));
}

void	_free_command_line(
			void *to_free,
			void *usrptr
			)
{
	(void)(usrptr);
	command_line_destroy(to_free);
}

void	*_prod_command__ss1(
			t_lr_stack_item *item,
			void *usrptr
			)
{
	t_subshell *const	ss = item[0].data.derived.data;

	(void)(usrptr);
	return (command_create(ss, COMMAND_SUBSHELL));
}

void	_free_command__ss1(
			void *to_free,
			void *usrptr
			)
{
	(void)(usrptr);
	command_destroy(to_free);
}

void	*_prod_command__ss2(
			t_lr_stack_item *item,
			void *usrptr
			)
{
	t_subshell *const		ss = item[0].data.derived.data;
	t_redirect_list *const	rl = item[1].data.derived.data;

	(void)(usrptr);
	if (subshell_add_rl(ss, rl))
		return (NULL);
	return (command_create(ss, COMMAND_SUBSHELL));
}

void	_free_command__ss2(
			void *to_free,
			void *usrptr
			)
{
	(void)(usrptr);
	command_destroy(to_free);
}

void	*_prod_command__sc(
			t_lr_stack_item *item,
			void *usrptr
			)
{
	t_simple_command *const	sc = item[0].data.derived.data;

	(void)(usrptr);
	return (command_create(sc, COMMAND_SIMPLE_COMMAND));
}

void	_free_command__sc(
			void *to_free,
			void *usrptr
			)
{
	(void)(usrptr);
	command_destroy(to_free);
}

void	*_prod_subshell(
			t_lr_stack_item *item,
			void *usrptr
			)
{
	t_and_or *const	and_or = item[1].data.derived.data;

	(void)(usrptr);
	return (subshell_create(and_or));
}

void	_free_subshell(
			void *to_free,
			void *usrptr
			)
{
	(void)(usrptr);
	subshell_destroy(to_free);
}

void	*_prod_and_or__1(
			t_lr_stack_item *item,
			void *usrptr
			)
{
	t_pipeline *const	pl = item[0].data.derived.data;

	(void)(usrptr);
	return (and_or_leaf(pl));
}

void	_free_and_or__1(
			void *to_free,
			void *usrptr
			)
{
	(void)(usrptr);
	and_or_destroy(to_free);
}

void	*_prod_and_or__3(
			t_lr_stack_item *item,
			void *usrptr
			)
{
	t_and_or *const		left = item[0].data.derived.data;
	t_logic_type const	type = item[1].data.token.data.logic_type;
	t_pipeline *const	pl = item[2].data.derived.data;

	(void)(usrptr);
	return (and_or_node(left, type, pl));
}

void	_free_and_or__3(
			void *to_free,
			void *usrptr
			)
{
	(void)(usrptr);
	and_or_destroy(to_free);
}

void	*_prod_pipeline__1(
			t_lr_stack_item *item,
			void *usrptr
			)
{
	t_command *const	command = item[0].data.derived.data;

	(void)(usrptr);
	return (pipeline_create(command));
}

void	_free_pipeline__1(
			void *to_free,
			void *usrptr
			)
{
	(void)(usrptr);
	pipeline_destroy(to_free);
}

void	*_prod_pipeline__3(
			t_lr_stack_item *item,
			void *usrptr
			)
{
	t_pipeline *const	pl = item[0].data.derived.data;
	t_command *const	command = item[2].data.derived.data;

	(void)(usrptr);
	if (pipeline_pushback(pl, command))
		return (NULL);
	return (pl);
}

void	_free_pipeline__3(
			void *to_free,
			void *usrptr
			)
{
	(void)(usrptr);
	pipeline_destroy(to_free);
}

void	*_prod_io_info(
			t_lr_stack_item *item,
			void *usrptr
			)
{
	t_io_type const	type = item[0].data.token.data.io_type;
	char *const		file = item[1].data.token.data.word;

	(void)(usrptr);
	return (io_info_create(type, file));
}

void	_free_io_info(
			void *to_free,
			void *usrptr
			)
{
	(void)(usrptr);
	io_info_destroy(to_free);
}

void	*_prod_progname(
			t_lr_stack_item *item,
			void *usrptr
			)
{
	char *const	word = item[0].data.token.data.word;

	(void)(usrptr);
	return ((t_progname)word);
}

void	_free_progname(
			void *to_free,
			void *usrptr
			)
{
	(void)(usrptr);
	free(to_free);
}

void	*_prod_arg_red__arg(
			t_lr_stack_item *item,
			void *usrptr
			)
{
	char *const	arg = item[0].data.token.data.word;

	(void)(usrptr);
	return (arg_red_create_arg(arg));
}

void	_free_arg_red__arg(
			void *to_free,
			void *usrptr
			)
{
	(void)(usrptr);
	arg_red_destroy(to_free);
}

void	*_prod_arg_red__io(
			t_lr_stack_item *item,
			void *usrptr
			)
{
	t_io_info *const	io_info = item[0].data.derived.data;

	(void)(usrptr);
	return (arg_red_create_redirect(io_info));
}

void	_free_arg_red__io(
			void *to_free,
			void *usrptr
			)
{
	(void)(usrptr);
	arg_red_destroy(to_free);
}

void	*_prod_arg_red_list__1(
			t_lr_stack_item *item,
			void *usrptr
			)
{
	t_arg_red *const	ar = item[0].data.derived.data;

	(void)(usrptr);
	return (args_redirect_list_create(ar));
}

void	_free_arg_red_list__1(
			void *to_free,
			void *usrptr
			)
{
	(void)(usrptr);
	args_redirect_list_destroy(to_free);
}

void	*_prod_arg_red_list__2(
			t_lr_stack_item *item,
			void *usrptr
			)
{
	t_args_redirect_list *const	arl = item[0].data.derived.data;
	t_arg_red *const			ar = item[1].data.derived.data;

	(void)(usrptr);
	if (args_redirect_list_pusback(arl, ar))
		return (NULL);
	return (arl);
}

void	_free_arg_red_list__2(
			void *to_free,
			void *usrptr
			)
{
	(void)(usrptr);
	args_redirect_list_destroy(to_free);
}

void	*_prod_redirect_list__1(
			t_lr_stack_item *item,
			void *usrptr
			)
{
	t_io_info *const	io_info = item[0].data.derived.data;

	(void)(usrptr);
	return (redirect_list_create(io_info));
}

void	_free_redirect_list__1(
			void *to_free,
			void *usrptr
			)
{
	(void)(usrptr);
	redirect_list_destroy(to_free);
}

void	*_prod_redirect_list__2(
			t_lr_stack_item *item,
			void *usrptr
			)
{
	t_redirect_list *const	rl = item[0].data.derived.data;
	t_io_info *const		io_info = item[1].data.derived.data;

	(void)(usrptr);
	if (redirect_list_pushback(rl, io_info))
		return (NULL);
	return (rl);
}

void	_free_redirect_list__2(
			void *to_free,
			void *usrptr
			)
{
	(void)(usrptr);
	redirect_list_destroy(to_free);
}
