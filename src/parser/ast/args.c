/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-boud <ale-boud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 20:26:45 by ale-boud          #+#    #+#             */
/*   Updated: 2023/12/11 23:34:15 by ale-boud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file args.c
 * @author ale-boud (ale-boud@student.42.fr)
 * @brief AST args function implementation.
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

t_args	*args_init(void)
{
	t_args	*args;

	args = malloc(sizeof(*args));
	if (args == NULL)
		return (NULL);
	args->alloced = 1;
	args->used = 0;
	args->args = malloc((args->alloced + 1) * sizeof(*args->args));
	if (args->args == NULL)
		return (free(args), NULL);
	args->args[0] = NULL;
	return (args);
}

t_args	*args_create(
			char *arg
			)
{
	t_args	*args;

	args = malloc(sizeof(*args));
	if (args == NULL)
		return (free(arg), NULL);
	args->alloced = 1;
	args->used = 0;
	args->args = malloc((args->alloced + 1) * sizeof(*args->args));
	if (args->args == NULL)
		return (free(arg), free(args), NULL);
	args->args[args->used++] = arg;
	args->args[args->used] = NULL;
	return (args);
}

int	args_pushback(
		t_args *args,
		char *arg
		)
{
	char	**tmp;

	if (args->used >= args->alloced)
	{
		tmp = ft_realloc(args->args,
				(args->alloced + 1) * sizeof(*args->args),
				(args->alloced * 2 + 1) * sizeof(*args->args));
		if (tmp == NULL)
			return (args_destroy(args), free(arg), 1);
		args->alloced *= 2;
		args->args = tmp;
	}
	args->args[args->used++] = arg;
	args->args[args->used] = NULL;
	return (0);
}

int	args_cat(
		t_args *args1,
		t_args *args2
		)
{
	char	**tmp;
	size_t	total_size;

	total_size = args1->used + args2->used;
	if (total_size > args1->alloced)
	{
		tmp = ft_realloc(args1->args,
				(args1->alloced + 1) * sizeof(*args1->args),
				(total_size + 1) * sizeof(*args1->args));
		if (tmp == NULL)
			return (args_destroy(args1), args_destroy(args2), 1);
		args1->alloced = total_size;
		args1->args = tmp;
	}
	ft_memcpy(args1->args + args1->used, args2->args,
		args2->used * sizeof(*args2->args));
	args2->used = 0;
	args1->used = total_size;
	args1->args[args1->used] = NULL;
	args_destroy(args2);
	return (0);
}

void	args_destroy(
			t_args *args
			)
{
	size_t	k;

	if (args != NULL)
	{
		if (args->args != NULL)
		{
			k = 0;
			while (k < args->used)
			{
				free(args->args[k]);
				++k;
			}
			free(args->args);
		}
		free(args);
	}
}
