/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-boud <ale-boud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 21:53:56 by ale-boud          #+#    #+#             */
/*   Updated: 2024/02/13 17:44:54 by ale-boud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file pipeline.c
 * @author ale-boud (ale-boud@student.42.fr)
 * @brief AST pipeline implementation.
 * @date 2023-12-11
 * @copyright Copyright (c) 2023
 */

// ************************************************************************** //
// *                                                                        * //
// * Includes.                                                              * //
// *                                                                        * //
// ************************************************************************** //

#include "parser/ast.h"

#include "utils.h"

// ************************************************************************** //
// *                                                                        * //
// * Header function.                                                       * //
// *                                                                        * //
// ************************************************************************** //

t_pipeline	*pipeline_create(
				t_command *command
				)
{
	t_pipeline	*pl;

	pl = malloc(sizeof(*pl));
	if (pl == NULL)
		return (command_destroy(command), NULL);
	pl->alloced = 1;
	pl->used = 1;
	pl->commands = malloc(sizeof(*pl->commands) * pl->alloced);
	if (pl->commands == NULL)
		return (free(pl), command_destroy(command), NULL);
	pl->commands[0] = *command;
	free(command);
	return (pl);
}

int	pipeline_pushback(
		t_pipeline *pl,
		t_command *command
		)
{
	t_command	*tmp;

	if (pl->used >= pl->alloced)
	{
		tmp = _realloc(pl->commands,
				pl->alloced * sizeof(*pl->commands),
				pl->alloced * 2 * sizeof(*pl->commands));
		if (tmp == NULL)
			return (pipeline_destroy(pl), command_destroy(command), 1);
		pl->alloced *= 2;
		pl->commands = tmp;
	}
	pl->commands[pl->used++] = *command;
	free(command);
	return (0);
}

void	pipeline_destroy(
			t_pipeline *pl
			)
{
	size_t	k;

	if (pl != NULL)
	{
		if (pl->commands != NULL)
		{
			k = 0;
			while (k < pl->used)
			{
				command_free(&pl->commands[k]);
				++k;
			}
			free(pl->commands);
		}
		free(pl);
	}
}
