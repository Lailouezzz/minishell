/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-boud <ale-boud@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 08:11:11 by amassias          #+#    #+#             */
/*   Updated: 2024/09/24 18:17:14 by ale-boud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file prompt.c
 * @author Antoine Massias (amassias@student.42lehavre.fr)
 * @date 2024-03-20
 * @copyright Copyright (c) 2024
 */

/* ************************************************************************** */
/*                                                                            */
/* Includes                                                                   */
/*                                                                            */
/* ************************************************************************** */

#include "core/exec.h"

#include <unistd.h>
#include <limits.h>
#include <libft.h>
#include <pwd.h>
#include <stdio.h>
#include <readline/readline.h>

/* ************************************************************************** */
/*                                                                            */
/* Defines                                                                    */
/*                                                                            */
/* ************************************************************************** */

#define HOST_NAME_MAX_LEN 512

#ifndef HOST_NAME_MAX
# define HOST_NAME_MAX 512
#endif

#define COLOR_CODE_RED 31
#define COLOR_CODE_GREEN 32

#define PROMPT_FMT_L1 "\e[0;32m(\e[1;34m%s@%s\e[0;32m)=[\e[1;37m%s\e[0;32m]"
#define PROMPT_FMT_L2 "\e[1;%dm$\e[0;0m "

// ************************************************************************** //
// *                                                                        * //
// * Utils declaration                                                      * //
// *                                                                        * //
// ************************************************************************** //

static const char	*_get_username(void);

/* ************************************************************************** */
/*                                                                            */
/* Header implementation                                                      */
/*                                                                            */
/* ************************************************************************** */

char	*ms_prompt(
			t_exec_ctx *ctx
			)
{
	static char			hostname[HOST_NAME_MAX + 1] = {0};
	const char			*username = _get_username();
	char				*cwd;
	char				*result;
	char				*line;

	if (gethostname(hostname, HOST_NAME_MAX))
		return (NULL);
	cwd = getcwd(NULL, 0);
	if (cwd == NULL)
		return (NULL);
	result = malloc(1 + snprintf(NULL, 0, PROMPT_FMT_L1 "\n" PROMPT_FMT_L2,
				username, hostname, cwd, 30));
	if (result == NULL)
		return (free(cwd), NULL);
	if (ctx->env_ctx->current_code)
		sprintf(result, PROMPT_FMT_L1 "\n" PROMPT_FMT_L2, username, hostname, cwd,
			COLOR_CODE_RED);
	else
		sprintf(result, PROMPT_FMT_L1 "\n" PROMPT_FMT_L2, username, hostname, cwd,
			COLOR_CODE_GREEN);
	free(cwd);
	line = readline(result);
	free(result);
	return (line);
}

// ************************************************************************** //
// *                                                                        * //
// * Utils implementation                                                   * //
// *                                                                        * //
// ************************************************************************** //

static const char	*_get_username(void)
{
	const int			euid = geteuid();
	const struct passwd	*pw = getpwuid(euid);

	if (pw == NULL)
		return (NULL);
	return (pw->pw_name);
}
