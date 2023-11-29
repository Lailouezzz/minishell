/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-boud <ale-boud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 06:12:13 by ale-boud          #+#    #+#             */
/*   Updated: 2023/11/29 14:22:30 by ale-boud         ###   ########.fr       */
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
#include <lr_parser.h>

#include "prod.h"

#include "token.h"
#include "table.h"
#include "ast.h"

t_lr_token	g_tokens[] = {
{.id = TOKEN_WORD, .data = "cat"},
{.id = TOKEN_WORD, .data = "file1"},
{.id = TOKEN_WORD, .data = "file2"},
{.id = TOKEN_IO, .data = &(t_io_type){IO_OUT}},
{.id = TOKEN_WORD, .data = "outfile"},
{.id = TOKEN_END, .data = NULL}
};

static void	command_print(t_command *command)
{
	char	**pstr;
	size_t	k;

	printf("Programme name: %s\nargs: ", command->pn);
	pstr = command->args;
	while (*pstr != NULL)
	{
		printf("\"%s\" ", *pstr);
		++pstr;
	}
	printf("NULL\n");
	k = 0;
	while (k < command->cio->used)
	{
		if (command->cio->io_infos[k]->type == IO_IN)
			printf("IN file: ");
		if (command->cio->io_infos[k]->type == IO_APPEND)
			printf("APPEND file: ");
		if (command->cio->io_infos[k]->type == IO_OUT)
			printf("OUT file: ");
		if (command->cio->io_infos[k]->type == IO_HEREDOC)
			printf("HEREDOC: ");
		printf("\"%s\"\n", command->cio->io_infos[k]->file);
		++k;
	}
}

int	main(void)
{
	t_lr_parser_ctx	ctx;
	void			*data;

	ctx.action_table = (t_lr_action *)g_lr_table;
	ctx.prod_count = PROD__COUNT;
	ctx.state_count = STATE__COUNT;
	ctx.token_count = TOKEN__COUNT;
	ctx.goto_table = (t_lr_state_id *)g_lr_goto_table;
	ctx.prod_cb = (t_lr_prod_cb *)g_prod_cbs;
	if (lr_parser_init(&ctx))
		return (EXIT_FAILURE);
	if (lr_parser_exec(&ctx, g_tokens, sizeof(g_tokens) / sizeof(*g_tokens),
			&data))
		return (EXIT_FAILURE);
	lr_parser_destroy(&ctx);
	command_print(data);
	command_destroy(data);
	return (EXIT_SUCCESS);
}
