/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-boud <ale-boud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 21:46:46 by ale-boud          #+#    #+#             */
/*   Updated: 2024/03/15 01:13:18 by ale-boud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file sig_handler.c
 * @author ale-boud (ale-boud@student.42.fr)
 * @brief The signal handlers of minishell.
 * @date 2024-01-22
 * @copyright Copyright (c) 2024
 */

// ************************************************************************** //
// *                                                                        * //
// * Includes.                                                              * //
// *                                                                        * //
// ************************************************************************** //

#include <stdio.h>
#include <readline/readline.h>
#include <signal.h>

#include <libft.h>

#include "core/exec.h"

volatile int	g_signo = 0;

// ************************************************************************** //
// *                                                                        * //
// * Signal handlers definition.                                            * //
// *                                                                        * //
// ************************************************************************** //

static void	_exec_sig_handler_interactive(
				int signo
				);

static void	_exec_sig_handler_in_execution(
				int signo
				);

// ************************************************************************** //
// *                                                                        * //
// * Header function.                                                       * //
// *                                                                        * //
// ************************************************************************** //

void	exec_set_interactive(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, _exec_sig_handler_interactive);
}

void	exec_set_in_execution(void)
{
	signal(SIGQUIT, _exec_sig_handler_in_execution);
	signal(SIGINT, _exec_sig_handler_in_execution);
}

// ************************************************************************** //
// *                                                                        * //
// * Signal handlers.                                                       * //
// *                                                                        * //
// ************************************************************************** //

static void	_exec_sig_handler_interactive(
				int signo
				)
{
	g_signo = signo;
	dprintf(STDOUT_FILENO, "\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

static void	_exec_sig_handler_in_execution(
				int signo
				)
{
	g_signo = signo;
	if (signo == SIGQUIT)
		dprintf(STDOUT_FILENO, "Quit (core dumped)\n");
	else if (signo == SIGINT)
		dprintf(STDOUT_FILENO, "\n");
}

// ************************************************************************** //
// *                                                                        * //
// * Header function.                                                       * //
// *                                                                        * //
// ************************************************************************** //

void	_exec_loop_handle_signal(
			t_exec_ctx *ctx
			)
{
	if (g_signo != 0)
		if (env_set_code(ctx->env_ctx, 128 + g_signo) != MS_OK)
			exec_cleanup_exit(ctx, MS_STATUS_FAILURE);
	g_signo = 0;
}
