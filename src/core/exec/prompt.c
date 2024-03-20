/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amassias <amassias@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 08:11:11 by amassias          #+#    #+#             */
/*   Updated: 2024/03/20 08:59:03 by amassias         ###   ########.fr       */
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

#define PROMPT_FMT_L1 "\e[0;32m(\e[1;34m%s@%s\e[0;32m)=[\e[1;37m%s\e[0;32m]"
#define PROMPT_FMT_L2 "\e[1;34m$\e[0;0m "

/* ************************************************************************** */
/*                                                                            */
/* Header implementation                                                      */
/*                                                                            */
/* ************************************************************************** */

char	*ms_prompt(void)
{
	static char	hostname[HOST_NAME_MAX + 1] = {0};
	const char	*login = getlogin();
	char		*cwd;
	char		*result;
	char		*line;

	if (gethostname(hostname, HOST_NAME_MAX))
		return (NULL);
	cwd = getcwd(NULL, 0);
	if (cwd == NULL)
		return (NULL);
	result = malloc(1 + snprintf(NULL, 0, PROMPT_FMT_L1 "\n" PROMPT_FMT_L2,
				login, hostname, cwd));
	if (result == NULL)
		return (free(cwd), NULL);
	sprintf(result, PROMPT_FMT_L1 "\n" PROMPT_FMT_L2, login, hostname, cwd);
	free(cwd);
	line = readline(result);
	free(result);
	return (line);
}
