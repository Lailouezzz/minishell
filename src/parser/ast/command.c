/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-boud <ale-boud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 22:20:54 by ale-boud          #+#    #+#             */
/*   Updated: 2023/12/11 22:27:31 by ale-boud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file command.c
 * @author ale-boud (ale-boud@student.42.fr)
 * @brief AST command function implementation.
 * @date 2023-12-11
 * @copyright Copyright (c) 2023
 */

// ************************************************************************** //
// *                                                                        * //
// * Includes.                                                              * //
// *                                                                        * //
// ************************************************************************** //

#include "parser/ast.h"

// ************************************************************************** //
// *                                                                        * //
// * Header function.                                                       * //
// *                                                                        * //
// ************************************************************************** //

t_command	*command_create(
				void *commandp,
				t_command_type type
				)
{
	t_command	*command;

	command = malloc(sizeof(*command));
	if (command == NULL)
	{
		if (type == COMMAND_SUBSHELL)
			subshell_destroy(commandp);
		if (type == COMMAND_SIMPLE_COMMAND)
			simple_command_destroy(commandp);
		return (NULL);
	}
	command->command = commandp;
	command->type = type;
	return (command);
}

void	command_destroy(
			t_command *command
			)
{
	if (command != NULL)
	{
		command_free(command);
		free(command);
	}
}

void	command_free(
			t_command *command
			)
{
	if (command != NULL)
	{
		if (command->type == COMMAND_SUBSHELL)
			subshell_destroy(command->command);
		else if (command->type == COMMAND_SIMPLE_COMMAND)
			simple_command_destroy(command->command);
	}
}
