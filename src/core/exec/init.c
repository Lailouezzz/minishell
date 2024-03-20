/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amassias <amassias@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 03:27:27 by ale-boud          #+#    #+#             */
/*   Updated: 2024/03/20 14:18:31 by amassias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file init.c
 * @author ale-boud (ale-boud@student.42.fr)
 * @brief The exec init function.
 * @date 2024-01-22
 * @copyright Copyright (c) 2024
 */

// ************************************************************************** //
// *                                                                        * //
// * Includes.                                                              * //
// *                                                                        * //
// ************************************************************************** //

#include <signal.h>

#include "core/exec.h"

// ************************************************************************** //
// *                                                                        * //
// * Header functions.                                                      * //
// *                                                                        * //
// ************************************************************************** //

void	exec_init(
			t_exec_ctx *ctx,
			t_env_ctx *env_ctx,
			t_lr_parser_ctx *parser_ctx
			)
{
	ctx->env_ctx = env_ctx;
	ctx->parser_ctx = parser_ctx;
	ctx->current_cl = NULL;
	ctx->current_line = NULL;
	ctx->tmp_std_fds[0] = -1;
	ctx->tmp_std_fds[1] = -1;
}
