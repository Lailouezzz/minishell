/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amassias <amassias@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 16:30:48 by amassias          #+#    #+#             */
/*   Updated: 2024/03/12 16:14:32 by amassias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file redirections.c
 * @author Antoine Massias (amassias@student.42lehavre.fr)
 * @date 2024-03-11
 * @copyright Copyright (c) 2024
 */

/* ************************************************************************** */
/*                                                                            */
/* Includes                                                                   */
/*                                                                            */
/* ************************************************************************** */

#include "core/_exec.h"

#include <fcntl.h>
#include <errno.h>

/* ************************************************************************** */
/*                                                                            */
/* Defines                                                                    */
/*                                                                            */
/* ************************************************************************** */

#define O_IN 0
#define O_OT 577
#define O_AP 1601

#define STDIN 0
#define STDOUT 1

/* ************************************************************************** */
/*                                                                            */
/* Helper protoypes                                                           */
/*                                                                            */
/* ************************************************************************** */

static char			*_prompt(void);

static void			_close_all(
						const int fds[2]
						);

static int			_create_heredoc(
						const char *delim
						);

static int			_open_redirection(
						t_io_info *io_info
						);

/* ************************************************************************** */
/*                                                                            */
/* Header implementation                                                      */
/*                                                                            */
/* ************************************************************************** */

bool	handle_redirect_list(
				const t_redirect_list *list
				)
{
	const int	io[2] = {-1, -1};
	t_io_info	*info;
	size_t		i;
	int			fd;

	if (list == NULL)
		return (false);
	info = list->io_infos;
	i = 0;
	while (i < list->used)
	{
		fd = _open_redirection(&info[i]);
		if (fd == -1)
			return (_close_all(io), true);
		if (info[i].io_type == IO_IN || info[i].io_type == IO_HEREDOC)
			(close(io[STDIN]), *((int *)&io[STDIN]) = fd);
		else
			(close(io[STDOUT]), *((int *)&io[STDOUT]) = fd);
		++i;
	}
	if (io[STDOUT] != -1 && dup2(io[STDOUT], STDOUT_FILENO) == -1)
		return (dprintf(2, "ALED"), _close_all(io), true);
	if (io[STDIN] != -1 && dup2(io[STDIN], STDIN_FILENO) == -1)
		return (dprintf(2, "ALED"), _close_all(io), true);
	return (false);
}

/* ************************************************************************** */
/*                                                                            */
/* Helper implementation                                                      */
/*                                                                            */
/* ************************************************************************** */

static char	*_prompt(void)
{
	dprintf(STDOUT_FILENO, "> ");
	return (get_next_line(STDIN_FILENO));
}

static void	_close_all(
				const int fds[2]
				)
{
	(close(STDIN_FILENO), close(fds[STDIN]));
	(close(STDOUT_FILENO), close(fds[STDOUT]));
}

static int	_create_heredoc(
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

static int	_open_redirection(
				t_io_info *io_info
				)
{
	int	fd;

	if (io_info->io_type == IO_IN)
		fd = open(io_info->file, O_RDONLY);
	else if (io_info->io_type == IO_OUT)
		fd = open(io_info->file, O_CREAT | O_WRONLY | O_TRUNC, 0666);
	else if (io_info->io_type == IO_APPEND)
		fd = open(io_info->file, O_CREAT | O_WRONLY | O_APPEND, 0666);
	else
		fd = _create_heredoc(io_info->file);
	if (fd != -1)
		return (fd);
	dprintf(STDERR_FILENO, MS);
	if (io_info->io_type == IO_HEREDOC)
		dprintf(STDERR_FILENO, "Cannot create heredoc\n");
	else
		perror(io_info->file);
	return (-1);
}
