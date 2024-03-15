/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-boud <ale-boud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 19:16:07 by amassias          #+#    #+#             */
/*   Updated: 2024/03/15 01:06:22 by ale-boud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file create_heredoc.c
 * @author Antoine Massias (amassias@student.42lehavre.fr)
 * @date 2024-03-12
 * @copyright Copyright (c) 2024
 */

/* ************************************************************************** */
/*                                                                            */
/* Includes                                                                   */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <sys/ioctl.h>
#include <errno.h>
#include <string.h>

#include "core/_exec.h"

/* ************************************************************************** */
/*                                                                            */
/* Helper protoypes                                                           */
/*                                                                            */
/* ************************************************************************** */

static char	*_prompt(void);

/* ************************************************************************** */
/*                                                                            */
/* Header implementation                                                      */
/*                                                                            */
/* ************************************************************************** */

int	create_heredoc(
		const char *delim,
		int *fd
		)
{
	FILE			*f;
	char			*line;
	const size_t	delim_length = ft_strlen(delim);
	int				airno;

	f = tmpfile();
	if (f == NULL)
		return (*fd = -1, 1);
	line = _prompt();
	while (line && g_signo != SIGINT)
	{
		if (ft_strncmp(delim, line, delim_length) == 0
			&& line + delim_length == (char *)u_get_end(line))
			break ;
		ft_putstr_fd(line, fileno(f));
		free(line);
		line = _prompt();
	}
	airno = errno;
	free(line);
	lseek(fileno(f), 0, SEEK_SET);
	*fd = dup(fileno(f));
	fclose(f);
	return (line == NULL && airno == 0 && g_signo != SIGINT);
}

/* ************************************************************************** */
/*                                                                            */
/* Helper implementation                                                      */
/*                                                                            */
/* ************************************************************************** */

static char	*_prompt(void)
{
	char			*r;

	ft_putstr_fd("> ", STDOUT_FILENO);
	ioctl(STDIN_FILENO, FIONBIO, (char *)(int []){1});
	errno = 0;
	r = get_next_line(STDIN_FILENO);
	while (r == NULL && errno == EAGAIN && g_signo != SIGINT)
	{
		errno = 0;
		r = get_next_line(STDIN_FILENO);
	}
	ioctl(STDIN_FILENO, FIONBIO, (char *)(int []){0});
	return (r);
}
