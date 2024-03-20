/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amassias <amassias@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 17:22:11 by ale-boud          #+#    #+#             */
/*   Updated: 2024/03/20 14:24:53 by amassias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file cleanup.c
 * @author ale-boud (ale-boud@student.42.fr)
 * @brief Minishell cleanup exit.
 * @date 2024-02-14
 * @copyright Copyright (c) 2024
 */

// ************************************************************************** //
// *                                                                        * //
// * Includes.                                                              * //
// *                                                                        * //
// ************************************************************************** //

#include <stdlib.h>
#include <stdio.h>
#include <readline/readline.h>
#include <unistd.h>

#include "core/exec.h"

// ************************************************************************** //
// *                                                                        * //
// * Header function.                                                       * //
// *                                                                        * //
// ************************************************************************** //

void	exec_cleanup_tmp_fds(
			t_exec_ctx *ctx
			)
{
	if (ctx->tmp_std_fds[0] >= 0)
		(close(ctx->tmp_std_fds[0]), ctx->tmp_std_fds[0] = -1);
	if (ctx->tmp_std_fds[1] >= 0)
		(close(ctx->tmp_std_fds[1]), ctx->tmp_std_fds[1] = -1);
}

noreturn void	exec_cleanup_exit(
					t_exec_ctx *ctx,
					t_ms_status code
					)
{
	free(ctx->current_line);
	command_line_destroy(ctx->current_cl);
	exec_cleanup_tmp_fds(ctx);
	env_ctx_destroy(ctx->env_ctx);
	rl_clear_history();
	exit(code);
}
