/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-boud <ale-boud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 06:12:13 by ale-boud          #+#    #+#             */
/*   Updated: 2024/02/08 16:43:49 by ale-boud         ###   ########.fr       */
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

int	main(int argc, char **argv, char **envp)
{
	t_lr_parser_ctx	parser_ctx;
	t_exec_ctx		ex_ctx;
	t_env_ctx		env_ctx;

	(void)(argc);
	(void)(argv);
	parser_ctx.prod_count = PROD__COUNT;
	parser_ctx.state_count = STATE__COUNT;
	parser_ctx.token_count = TOKEN__COUNT;
	parser_ctx.action_table = (t_lr_action *)g_lr_table;
	parser_ctx.goto_table = (t_lr_state_id *)g_lr_goto_table;
	parser_ctx.prod_cb = (t_lr_prod_cb *)g_prod_cbs;
	parser_ctx.token_free_cbs = (t_lr_token_free_cb *)g_tok_free_cbs;
	env_ctx_init(&env_ctx, argv[0], envp);
	exec_init(&ex_ctx, &env_ctx, &parser_ctx);
	exec_loop(&ex_ctx);
	rl_clear_history();
	return (env_ctx.current_code);
}
