/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   restore_termios.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-boud <ale-boud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 01:10:15 by ale-boud          #+#    #+#             */
/*   Updated: 2024/03/15 01:22:00 by ale-boud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file restore_termios.c
 * @author ale-boud (ale-boud@student.42.fr)
 * @brief Termios restore to default.
 * @date 2024-03-15
 * @copyright Copyright (c) 2024
 */

// ************************************************************************** //
// *                                                                        * //
// * Includes.                                                              * //
// *                                                                        * //
// ************************************************************************** //

#include <termios.h>
#include <unistd.h>

#include "core/exec.h"

// ************************************************************************** //
// *                                                                        * //
// * Header function.                                                       * //
// *                                                                        * //
// ************************************************************************** //

void	env_ctx_restore_termios(
			t_env_ctx *env_ctx
			)
{
	if (env_ctx->istty)
		tcsetattr(STDIN_FILENO, TCSAFLUSH, &env_ctx->tstart);
}
