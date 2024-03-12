/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amassias <amassias@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 19:16:07 by amassias          #+#    #+#             */
/*   Updated: 2024/03/12 19:19:08 by amassias         ###   ########.fr       */
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
	dprintf(STDOUT_FILENO, "Xheredoc> ");
	line = get_next_line(STDIN_FILENO);
	while (line)
	{
		if (ft_strncmp(delim, line, delim_length) == 0
			&& line + delim_length == (char *)u_get_end(line))
			break ;
		ft_putstr_fd(line, fileno(f));
		dprintf(STDOUT_FILENO, "Xheredoc> ");
		(free(line), line = get_next_line(STDIN_FILENO));
	}
	free(line);
	lseek(fileno(f), 0, SEEK_SET);
	fd = dup(fileno(f));
	fclose(f);
	return (fd);
}
