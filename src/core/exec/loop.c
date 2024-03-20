/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-boud <ale-boud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 03:27:07 by ale-boud          #+#    #+#             */
/*   Updated: 2024/03/20 13:58:44 by ale-boud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file loop.c
 * @author ale-boud (ale-boud@student.42.fr)
 * @brief The execution loop of minishell.
 * @date 2024-01-22
 * @copyright Copyright (c) 2024
 */

// ************************************************************************** //
// *                                                                        * //
// * Includes.                                                              * //
// *                                                                        * //
// ************************************************************************** //

#include <stdio.h>
#include <stdnoreturn.h>

#include <readline/readline.h>
#include <readline/history.h>

#include <libft.h>

#include "core/exec.h"

#include "tokenizer/tokenizer.h"
#include "utils.h"

// ************************************************************************** //
// *                                                                        * //
// * Defines.                                                               * //
// *                                                                        * //
// ************************************************************************** //

#define ERR_PARSE "%s: syntax error near unexpected token `%c'"

// ************************************************************************** //
// *                                                                        * //
// * Helper function definition.                                            * //
// *                                                                        * //
// ************************************************************************** //

static t_ms_error	_exec_loop_parse(
						t_exec_ctx *ctx,
						char **pstr
						);

static t_ms_error	__exec_loop_parse_tokenize(
						t_exec_ctx *ctx,
						t_lr_token_list *lrtoks,
						char **pstr
						);

static t_lr_error	__exec_loop_parse_exec(
						t_exec_ctx *ctx,
						t_lr_token_list *lrtoks,
						t_command_line **cl
						);

// ************************************************************************** //
// *                                                                        * //
// * Header functions.                                                      * //
// *                                                                        * //
// ************************************************************************** //

void	exec_loop(
			t_exec_ctx *ctx
			)
{
	t_ms_error		r;
	char			*pstr;

	exec_set_interactive();
	ctx->current_line = NULL;
	pstr = ms_prompt(ctx);
	while (pstr != NULL)
	{
		_exec_loop_handle_signal(ctx);
		ctx->current_line = pstr;
		while (ft_isspace(*pstr))
			++pstr;
		if (*pstr != '\0')
		{
			add_history(ctx->current_line);
			r = exec_loop_exec(ctx);
			if (r != MS_OK && r != MS_SYNTAX_ERROR && r != MS_EMPTY_COMMAND)
				break ;
		}
		free(ctx->current_line);
		ctx->current_line = NULL;
		pstr = ms_prompt(ctx);
	}
	free(ctx->current_line);
}

t_ms_error	exec_loop_exec(
				t_exec_ctx *ctx
				)
{
	t_ms_error		r;
	char			*pstr;

	pstr = ctx->current_line;
	r = _exec_loop_parse(ctx, &pstr);
	if (r == MS_EMPTY_COMMAND)
		return (r);
	if (r != MS_OK)
	{
		if (r != MS_SYNTAX_ERROR)
			return (MS_FATAL);
		dprintf(STDERR_FILENO, ERR_PARSE "\n",
			ctx->env_ctx->pn, *(pstr - 1));
		if (env_set_code(ctx->env_ctx, 2) != MS_OK)
			exec_cleanup_exit(ctx, MS_STATUS_FAILURE);
		return (r);
	}
	r = exec_exec(ctx, ctx->current_cl);
	(exec_set_interactive(), command_line_destroy(ctx->current_cl));
	ctx->current_cl = NULL;
	if (r != MS_OK && r != MS_COMMAND_NOT_FOUND && r != MS_PERM_DENIED)
		return (MS_FATAL);
	return (MS_OK);
}

// ************************************************************************** //
// *                                                                        * //
// * Helper function definition.                                            * //
// *                                                                        * //
// ************************************************************************** //

static	t_ms_error	_exec_loop_parse(
						t_exec_ctx *ctx,
						char **pstr
						)
{
	t_lr_token_list	lrtoks;
	int				r;

	lr_parser_init(ctx->parser_ctx, NULL);
	r = __exec_loop_parse_tokenize(ctx, &lrtoks, pstr);
	if (r != MS_OK)
		return (r);
	if (lrtoks.lrtoks[0].id == TOKEN_END)
		return (free(lrtoks.lrtoks),
			lr_parser_destroy(ctx->parser_ctx), MS_EMPTY_COMMAND);
	while (42 > 01)
	{
		r = __exec_loop_parse_exec(ctx, &lrtoks, &ctx->current_cl);
		free(lrtoks.lrtoks);
		if (r == LR_SYNTAX_ERROR)
			return (MS_SYNTAX_ERROR);
		if (r == LR_ACCEPT)
			break ;
		if (r != LR_ACCEPT && r != LR_OK)
			return (MS_FATAL);
		r = __exec_loop_parse_tokenize(ctx, &lrtoks, pstr);
		if (r != MS_OK)
			return (r);
	}
	return (lr_parser_destroy(ctx->parser_ctx), MS_OK);
}

static t_ms_error	__exec_loop_parse_tokenize(
						t_exec_ctx *ctx,
						t_lr_token_list *lrtoks,
						char **pstr
						)
{
	t_ms_error	r;

	while (42 > 01)
	{
		r = tokenize(lrtoks, ctx->env_ctx, (const char **)pstr);
		if (r != MS_OK)
			return (lr_parser_destroy(ctx->parser_ctx), r);
		if (lrtoks->used != 0)
			return (r);
		free(lrtoks->lrtoks);
	}
}

static	t_lr_error	__exec_loop_parse_exec(
						t_exec_ctx *ctx,
						t_lr_token_list *lrtoks,
						t_command_line **cl
						)
{
	int			r;
	size_t		k;
	t_lr_token	*lrtok;

	k = 0;
	r = LR_OK;
	while (k < lrtoks->used)
	{
		lrtok = lrtoks->lrtoks + k;
		r = lr_parser_exec(ctx->parser_ctx, lrtok, (void **)cl);
		if (r != LR_OK && r != LR_ACCEPT)
			break ;
		++k;
	}
	if (k != lrtoks->used)
		while (k < lrtoks->used)
			if (g_tok_free_cbs[lrtoks->lrtoks[k++].id] != NULL)
				g_tok_free_cbs[lrtoks->lrtoks[k - 1].id](
					&lrtoks->lrtoks[k - 1].data);
	return (r);
}
