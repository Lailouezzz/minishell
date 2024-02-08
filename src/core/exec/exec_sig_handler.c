/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_sig_handler.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-boud <ale-boud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 21:46:46 by ale-boud          #+#    #+#             */
/*   Updated: 2024/02/08 15:55:47 by ale-boud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file exec_sig_handler.c
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

#include <readline/readline.h>
#include <signal.h>

#include "core/exec.h"

#include "utils.h"


volatile int	g_signo;


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
	(void)(signo);
	ft_putstr_fd("\n", STDOUT_FILENO);
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
		ft_putstr_fd("Quit (core dumped)\n", STDOUT_FILENO);
	else if (signo == SIGINT)
		ft_putstr_fd("\n", STDOUT_FILENO);
}
