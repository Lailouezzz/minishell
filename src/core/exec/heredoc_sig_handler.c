/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_sig_handler.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-boud <ale-boud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 20:27:50 by ale-boud          #+#    #+#             */
/*   Updated: 2024/03/15 01:10:30 by ale-boud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file heredoc_sig_handler.c
 * @author ale-boud (ale-boud@student.42.fr)
 * @brief Here doc sig handler.
 * @date 2024-03-14
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
#include <unistd.h>
#include <termios.h>

#include <libft.h>

#include "core/exec.h"

// ************************************************************************** //
// *                                                                        * //
// * Signal handlers definition.                                            * //
// *                                                                        * //
// ************************************************************************** //

static void	_exec_sig_handler_in_heredoc(
				int signo
				);

// ************************************************************************** //
// *                                                                        * //
// * Header function.                                                       * //
// *                                                                        * //
// ************************************************************************** //

void	exec_set_in_heredoc(
			t_exec_ctx *ctx
			)
{
	struct termios	tty;

	if (ctx->env_ctx->istty)
	{
		tcgetattr(STDIN_FILENO, &tty);
		tty.c_lflag &= ~(ECHOCTL);
		tcsetattr(STDIN_FILENO, TCSAFLUSH, &tty);
	}
	g_signo = 0;
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, _exec_sig_handler_in_heredoc);
}

// ************************************************************************** //
// *                                                                        * //
// * Signal handlers.                                                       * //
// *                                                                        * //
// ************************************************************************** //

static void	_exec_sig_handler_in_heredoc(
				int signo
				)
{
	if (signo == SIGINT)
	{
		ft_putstr_fd("^C\n", STDOUT_FILENO);
		g_signo = signo;
	}
}
