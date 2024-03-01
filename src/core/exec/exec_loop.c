/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-boud <ale-boud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 03:27:07 by ale-boud          #+#    #+#             */
/*   Updated: 2024/02/16 17:11:46 by ale-boud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file exec_loop.c
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
// * Helper function definition.                                            * //
// *                                                                        * //
// ************************************************************************** //

static t_ms_error	_exec_loop_exec(
						t_exec_ctx *ctx
						);

static t_ms_error	_exec_loop_parse(
						t_exec_ctx *ctx,
						char **pstr
						);

static t_lr_error	__exec_loop_parse_exec(
						t_exec_ctx *ctx,
						t_lr_token_list *lrtoks,
						t_command_line **cl
						);

static void			_exec_loop_handle_signal(
						t_exec_ctx *ctx
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
	pstr = readline(MS_PROMPT);
	while (pstr != NULL)
	{
		_exec_loop_handle_signal(ctx);
		ctx->current_line = pstr;
		while (ft_isspace(*pstr))
			++pstr;
		if (*pstr != '\0')
			add_history(pstr);
		if (*pstr != '\0')
		{
			r = _exec_loop_exec(ctx);
			if (r != MS_OK && r != MS_SYNTAX_ERROR)
				break ;
		}
		free(ctx->current_line);
		ctx->current_line = NULL;
		pstr = readline(MS_PROMPT);
	}
	free(ctx->current_line);
}

// ************************************************************************** //
// *                                                                        * //
// * Helper function definition.                                            * //
// *                                                                        * //
// ************************************************************************** //

static	t_ms_error	_exec_loop_exec(
						t_exec_ctx *ctx
						)
{
	t_ms_error		r;
	char			*pstr;

	pstr = ctx->current_line;
	r = _exec_loop_parse(ctx, &pstr);
	if (r != MS_OK)
	{
		if (r == MS_SYNTAX_ERROR)
		{
			printf("%s: parse error near unexpected token `%c`\n",
				ctx->env_ctx->pn, *(pstr - 1));
			if (env_set_code(ctx->env_ctx, 2) != MS_OK)
				exec_cleanup_exit(ctx, MS_STATUS_FAILURE);
			return (r);
		}
		return (MS_FATAL);
	}
	exec_set_in_execution();
	r = exec_exec(ctx, ctx->current_cl);
	(exec_set_interactive(), command_line_destroy(ctx->current_cl));
	ctx->current_cl = NULL;
	if (r != MS_OK && r != MS_COMMAND_NOT_FOUND && r != MS_PERM_DENIED)
		return (MS_FATAL);
	return (MS_OK);
}

static	t_ms_error	_exec_loop_parse(
						t_exec_ctx *ctx,
						char **pstr
						)
{
	t_lr_token_list	lrtoks;
	int				r;

	lr_parser_init(ctx->parser_ctx, NULL);
	while (42 > 01)
	{
		r = tokenize(&lrtoks, ctx->env_ctx, (const char **)pstr);
		if (r != MS_OK)
		{
			lr_parser_destroy(ctx->parser_ctx);
			return (r);
		}
		r = __exec_loop_parse_exec(ctx, &lrtoks, &ctx->current_cl);
		free(lrtoks.lrtoks);
		if (r == LR_SYNTAX_ERROR)
			return (MS_SYNTAX_ERROR);
		if (r == LR_ACCEPT)
			break ;
		if (r != LR_ACCEPT && r != LR_OK)
			return (MS_FATAL);
	}
	lr_parser_destroy(ctx->parser_ctx);
	if (r != LR_ACCEPT)
		return (MS_SYNTAX_ERROR);
	return (MS_OK);
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

static	void	_exec_loop_handle_signal(
					t_exec_ctx *ctx
					)
{
	if (g_signo != 0)
		if (env_set_code(ctx->env_ctx, 128 + g_signo) != MS_OK)
			exec_cleanup_exit(ctx, MS_STATUS_FAILURE);
	g_signo = 0;
}
