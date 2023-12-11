/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-boud <ale-boud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 06:12:13 by ale-boud          #+#    #+#             */
/*   Updated: 2023/12/11 17:48:40 by ale-boud         ###   ########.fr       */
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

#include "prod.h"

#include "tokenizer/tokenizer.h"
#include "table.h"
#include "ast.h"

int	main(void)
{
	t_lr_parser_ctx	ctx;
	t_lr_token_list	lrtoks;
	void			*data;
	char			*pstr;
	int				r;

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
	pstr = readline("minishell> ");
	void *tmp = pstr;
	const char *convtable[TOKEN__COUNT] = {
	[TOKEN_WORD] = "TOKEN_WORD",

	[TOKEN_IO] = "TOKEN_IO",

	[TOKEN_AND_OR] = "TOKEN_AND_OR",

	[TOKEN_PIPE] = "TOKEN_PIPE",

	[TOKEN_OBRACKET] = "TOKEN_OBRACKET",

	[TOKEN_CBRACKET] = "TOKEN_CBRACKET",

	[TOKEN_END] = "TOKEN_END",
	};
	while (*pstr != '\0')
	{
		while (42)
		{
			if (tokenize(&lrtoks, (const char **)&pstr))
			{
				printf("TOKENIZE ERROR\n");
				lr_parser_destroy(&ctx);
				free(tmp);
				return (EXIT_FAILURE);
			}
			size_t k = 0;
			int brk = 0;
			while (k < lrtoks.used)
			{
				t_lr_token *const lrtok = lrtoks.lrtoks + k;
				if (lrtok->id == TOKEN_WORD)
					{printf("TOKEN_WORD: %s\n", lrtok->data.word);}
				else
					printf("%s\n", convtable[lrtok->id]);
				r = lr_parser_exec(&ctx, lrtok, &data);
				if (r == MP_ERROR)
				{
					fprintf(stderr, "Syntax error!\n");
					lr_parser_init(&ctx, NULL);
					brk = 1;
				}
				if (r == MP_ACCEPT)
				{
					printf("CONGRATULATION YOU KNOW SHELL\n");
					brk = 1;
				}
				++k;
			}
			lrtoks_destroy(&lrtoks);
			if (brk)
				break ;
			// if (lrtok.id == TOKEN_WORD)
			// {
			// 	printf("TOKEN_WORD: %s\n", lrtok.data.word);
			// }
			// else
			// {
			// 	printf("%s\n", convtable[lrtok.id]);
			// }
			// r = lr_parser_exec(&ctx, &lrtok, (void **)&data);
			// if (r == MP_ERROR)
			// {
			// 	if (g_tok_free_cbs[lrtok.id] != NULL)
			// 		g_tok_free_cbs[lrtok.id](&lrtok.data);
			// 	fprintf(stderr, "Syntax error!\n");
			// 	lr_parser_init(&ctx, NULL);
			// 	break ;
			// }
			// if (r == MP_ACCEPT)
			// {
			// 	printf("Expression accepted.\n");
			// 	break ;
			// }
		}
		free(tmp);
		pstr = readline("minishell> ");
		tmp = pstr;
	}
	free(tmp);
	rl_clear_history();
	lr_parser_destroy(&ctx);
	return (EXIT_SUCCESS);
}
