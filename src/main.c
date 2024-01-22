/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-boud <ale-boud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 06:12:13 by ale-boud          #+#    #+#             */
/*   Updated: 2024/01/22 06:58:20 by ale-boud         ###   ########.fr       */
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

int	main(void)
{
	t_lr_parser_ctx	ctx;
	t_exec_ctx		exctx;

	ctx.prod_count = PROD__COUNT;
	ctx.state_count = STATE__COUNT;
	ctx.token_count = TOKEN__COUNT;
	ctx.action_table = (t_lr_action *)g_lr_table;
	ctx.goto_table = (t_lr_state_id *)g_lr_goto_table;
	ctx.prod_cb = (t_lr_prod_cb *)g_prod_cbs;
	ctx.token_free_cbs = (t_lr_token_free_cb *)g_tok_free_cbs;
	exec_init(&exctx, NULL, &ctx);
	exec_loop(&exctx);
	return (0xdeadbeef);
}
