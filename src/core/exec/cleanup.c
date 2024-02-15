/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amassias <amassias@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 17:22:11 by ale-boud          #+#    #+#             */
/*   Updated: 2024/02/15 13:21:14 by amassias         ###   ########.fr       */
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
	exit(code);
}
