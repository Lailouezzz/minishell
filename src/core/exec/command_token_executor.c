/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_token_executor.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amassias <amassias@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 18:15:00 by amassias          #+#    #+#             */
/*   Updated: 2024/03/14 15:04:24 by amassias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file command_token_executor.c
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

/* ************************************************************************** */
/*                                                                            */
/* Header implementation                                                      */
/*                                                                            */
/* ************************************************************************** */

t_ms_error	execute_simple_command(
				t_exec_ctx *ctx,
				t_simple_command *command
				)
{
	t_ms_error	error;

	if (handle_redirect_list(command->redirect_list))
		exec_cleanup_exit(ctx, 1);
	env_ctx_heredocs_cleanup(ctx->env_ctx);
	error = run_command(
			ctx,
			command->pn,
			(const char **)command->args->args);
	return (error);
}

t_ms_error	execute_subshell(
				t_exec_ctx *ctx,
				t_subshell *command
				)
{
	t_ms_error	error;

	error = MS_OK;
	if (handle_redirect_list(command->redirect_list))
		exec_cleanup_exit(ctx, 1);
	env_ctx_heredocs_cleanup(ctx->env_ctx);
	and_or_executor(ctx, command->and_or, &error);
	return (error);
}
