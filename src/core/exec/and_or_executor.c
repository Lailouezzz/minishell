/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   and_or_executor.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amassias <amassias@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 18:18:45 by amassias          #+#    #+#             */
/*   Updated: 2024/03/11 18:23:45 by amassias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file and_or_executor.c
 * @author Antoine Massias (amassias@student.42lehavre.fr)
 * @date 2024-03-11
 * @copyright Copyright (c) 2024
 */

/* ************************************************************************** */
/*                                                                            */
/* Includes                                                                   */
/*                                                                            */
/* ************************************************************************** */

#include "core/_exec.h"
#include <signal.h>

/* ************************************************************************** */
/*                                                                            */
/* Header implementation                                                      */
/*                                                                            */
/* ************************************************************************** */

bool	and_or_executor(
			t_exec_ctx *ctx,
			const t_and_or *and_or,
			t_ms_error *error
			)
{
	bool			should_stop;
	t_logic_type	logic_type;
	int				*current_code;

	if (and_or->left != NULL)
		if (and_or_executor(ctx, and_or->left, error))
			return (true);
	should_stop = false;
	logic_type = and_or->logic_type;
	current_code = &ctx->env_ctx->current_code;
	if (and_or->left == NULL
		|| (*current_code == MS_STATUS_OK) ^ (logic_type == LOGIC_OR))
		should_stop = execute_pipeline(ctx, and_or->right_pipeline, error);
	return (should_stop || *error != MS_OK || g_signo == SIGINT);
}
