/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-boud <ale-boud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 06:12:13 by ale-boud          #+#    #+#             */
/*   Updated: 2024/03/15 00:41:56 by ale-boud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file main.c
 * @author ale-boud (ale-boud@student.42.fr)
 * @brief The main testing mouahahahah
 * @date 2023-11-29
 * @copyright Copyright (c) 2023
 */

// ************************************************************************** //
// *                                                                        * //
// * Includes.                                                              * //
// *                                                                        * //
// ************************************************************************** //

#include <stdlib.h>
#include <stdio.h>
#include <readline/readline.h>
#include <lr_parser.h>

#include "parser/prod.h"
#include "tokenizer/tokenizer.h"
#include "parser/table.h"
#include "parser/ast.h"

#include "core/exec.h"

#include <libft.h>

// ************************************************************************** //
// *                                                                        * //
// * Helper functions definition.                                           * //
// *                                                                        * //
// ************************************************************************** //

static void	_setup_parser_ctx(
				t_lr_parser_ctx *parser_ctx
				);

// ************************************************************************** //
// *                                                                        * //
// * MINISHELL MAIN.                                                        * //
// *                                                                        * //
// ************************************************************************** //

int	main(int argc, char **argv, char **envp)
{
	t_lr_parser_ctx	parser_ctx;
	t_exec_ctx		ex_ctx;
	t_env_ctx		env_ctx;

	(void)argc;
	_setup_parser_ctx(&parser_ctx);
	if (env_ctx_init(&env_ctx, argv[0], envp) != MS_OK)
	{
		ft_putstr_fd("minishell: fatal error.\n", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	exec_init(&ex_ctx, &env_ctx, &parser_ctx);
	exec_loop(&ex_ctx);
	env_ctx_destroy(&env_ctx);
	rl_clear_history();
	ft_putstr_fd("exit\n", STDOUT_FILENO);
	return (env_ctx.current_code);
}

// ************************************************************************** //
// *                                                                        * //
// * Helper function.                                                       * //
// *                                                                        * //
// ************************************************************************** //

static void	_setup_parser_ctx(
				t_lr_parser_ctx *parser_ctx
				)
{
	parser_ctx->prod_count = PROD__COUNT;
	parser_ctx->state_count = STATE__COUNT;
	parser_ctx->token_count = TOKEN__COUNT;
	parser_ctx->action_table = (t_lr_action *)g_lr_table;
	parser_ctx->goto_table = (t_lr_state_id *)g_lr_goto_table;
	parser_ctx->prod_cb = (t_lr_prod_cb *)g_prod_cbs;
	parser_ctx->token_free_cbs = (t_lr_token_free_cb *)g_tok_free_cbs;
}
