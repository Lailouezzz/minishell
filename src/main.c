/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-boud <ale-boud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 06:12:13 by ale-boud          #+#    #+#             */
/*   Updated: 2024/03/20 13:59:47 by ale-boud         ###   ########.fr       */
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

static void				_setup_parser_ctx(
							t_lr_parser_ctx *parser_ctx
							);

noreturn static void	_exec_command(
							char *command,
							t_exec_ctx *ctx
							);

// ************************************************************************** //
// *                                                                        * //
// * MINISHELL MAIN.                                                        * //
// *                                                                        * //
// ************************************************************************** //

int	main(int argc, char **argv, char **envp)
{
	t_lr_parser_ctx	parser_ctx;
	t_exec_ctx		ctx;
	t_env_ctx		env_ctx;

	(void)argc;
	_setup_parser_ctx(&parser_ctx);
	if (env_ctx_init(&env_ctx, argv[0], envp) != MS_OK)
	{
		ft_putstr_fd("minishell: fatal error.\n", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	exec_init(&ctx, &env_ctx, &parser_ctx);
	if (argc == 3 && ft_strncmp("-c", argv[1], 2) == 0)
		_exec_command(argv[2], &ctx);
	else if (argc == 1)
		exec_loop(&ctx);
	else
	{
		ft_putstr_fd("minishell: invalid argument.\n", STDERR_FILENO);
		env_ctx.current_code = 1;
	}
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

noreturn static void	_exec_command(
							char *command,
							t_exec_ctx *ctx
							)
{
	ctx->current_line = ft_strdup(command);
	if (ctx->current_line == NULL)
		exec_cleanup_exit(ctx, MS_STATUS_FAILURE);
	if (exec_loop_exec(ctx) != MS_OK)
		exec_cleanup_exit(ctx, MS_STATUS_FAILURE);
	exec_cleanup_exit(ctx, ctx->env_ctx->current_code);
}
