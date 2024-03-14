/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amassias <amassias@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 19:16:07 by amassias          #+#    #+#             */
/*   Updated: 2024/03/13 13:25:12 by amassias         ###   ########.fr       */
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
		const char *delim
		)
{
	FILE	*f;
	char	*line;
	size_t	delim_length;
	int		fd;

	f = tmpfile();
	if (f == NULL)
		return (-1);
	delim_length = ft_strlen(delim);
	line = _prompt();
	while (line)
	{
		if (ft_strncmp(delim, line, delim_length) == 0
			&& line + delim_length == (char *)u_get_end(line))
			break ;
		ft_putstr_fd(line, fileno(f));
		free(line);
		line = _prompt();
	}
	free(line);
	lseek(fileno(f), 0, SEEK_SET);
	fd = dup(fileno(f));
	fclose(f);
	return (fd);
}

/* ************************************************************************** */
/*                                                                            */
/* Helper implementation                                                      */
/*                                                                            */
/* ************************************************************************** */

static char	*_prompt(void)
{
	dprintf(STDOUT_FILENO, "heredoc> ");
	return (get_next_line(STDIN_FILENO));
}
