/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-boud <ale-boud@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 17:22:11 by ale-boud          #+#    #+#             */
/*   Updated: 2024/02/15 20:41:03 by ale-boud         ###   ########.fr       */
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

#include "core/exec.h"

// ************************************************************************** //
// *                                                                        * //
// * Header function.                                                       * //
// *                                                                        * //
// ************************************************************************** //

noreturn void	exec_cleanup_exit(
					t_exec_ctx *ctx,
					t_ms_status code
					)
{
	free(ctx->current_line);
	command_line_destroy(ctx->current_cl);
	env_ctx_destroy(ctx->env_ctx);
	rl_clear_history();
	exit(code);
}
