/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-boud <ale-boud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 06:12:13 by ale-boud          #+#    #+#             */
/*   Updated: 2023/12/01 23:08:17 by ale-boud         ###   ########.fr       */
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

#include "tokenizer/tokenizer.h"
#include "table.h"
#include "ast.h"

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
	if (command->cio == NULL)
		return ;
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

int	main(int argc, char **argv)
{
	t_lr_parser_ctx	ctx;
	t_lr_token		lrtok;
	t_command		*data;
	const char		*pstr;
	int				r;

	if (argc != 2)
		return (EXIT_FAILURE);
	ctx.prod_count = PROD__COUNT;
	ctx.state_count = STATE__COUNT;
	ctx.token_count = TOKEN__COUNT;
	ctx.action_table = (t_lr_action *)g_lr_table;
	ctx.goto_table = (t_lr_state_id *)g_lr_goto_table;
	ctx.prod_cb = (t_lr_prod_cb *)g_prod_cbs;
	ctx.token_free_cbs = (t_lr_token_free_cb *)g_tok_free_cbs;
	if (lr_parser_init(&ctx, NULL))
		return (EXIT_FAILURE);
	r = MP_OK;
	pstr = argv[1];
	while (r == MP_OK)
	{
		if (tokenize(&lrtok, &pstr))
		{
			lr_parser_destroy(&ctx);
			return (EXIT_FAILURE);
		}
		r = lr_parser_exec(&ctx, &lrtok, (void **)&data);
		if (r == MP_ERROR)
		{
			if (g_tok_free_cbs[lrtok.id] != NULL)
				g_tok_free_cbs[lrtok.id](&lrtok.data);
			fprintf(stderr, "Syntax error!\n");
			return (EXIT_FAILURE);
		}
	}
	command_print(data);
	lr_parser_destroy(&ctx);
	command_destroy(data);
	return (EXIT_SUCCESS);
}
