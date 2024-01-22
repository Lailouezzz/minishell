/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-boud <ale-boud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 03:27:07 by ale-boud          #+#    #+#             */
/*   Updated: 2024/01/22 06:53:25 by ale-boud         ###   ########.fr       */
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

#include <readline/readline.h>
#include <readline/history.h>

#include "tokenizer/tokenizer.h"
#include "core/exec.h"

// ************************************************************************** //
// *                                                                        * //
// * Helper function definition.                                            * //
// *                                                                        * //
// ************************************************************************** //

static	t_ms_error	_exec_loop_parse(
						t_exec_ctx *ctx,
						char *pstr,
						t_command_line **cl
						);


static	t_lr_error	__exec_loop_parse_exec(
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
	char			*pstr;
	int				r;
	t_command_line	*cl;

	pstr = readline(MS_PROMPT);
	while (pstr != NULL)
	{
		add_history(pstr);
		r = _exec_loop_parse(ctx, pstr, &cl);
		if (r != MS_OK)
			break ;
		command_line_destroy(cl);
		free(pstr);
		pstr = readline(MS_PROMPT);
	}
	free(pstr);
	exit(EXIT_SUCCESS);
}

// ************************************************************************** //
// *                                                                        * //
// * Helper function definition.                                            * //
// *                                                                        * //
// ************************************************************************** //

static	t_ms_error	_exec_loop_parse(
						t_exec_ctx *ctx,
						char *pstr,
						t_command_line **cl
						)
{
	t_lr_token_list	lrtoks;
	int				r;

	lr_parser_init(ctx->parser_ctx, NULL);
	while (42)
	{
		r = tokenize(&lrtoks, (const char **)&pstr);
		if (r != MS_OK)
		{
			lr_parser_destroy(ctx->parser_ctx);
			return (r);
		}
		r = __exec_loop_parse_exec(ctx, &lrtoks, cl);
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
