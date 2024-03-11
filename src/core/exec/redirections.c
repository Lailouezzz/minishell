/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amassias <amassias@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 16:30:48 by amassias          #+#    #+#             */
/*   Updated: 2024/03/11 19:04:11 by amassias         ###   ########.fr       */
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

/* ************************************************************************** */
/*                                                                            */
/* Helper protoypes                                                           */
/*                                                                            */
/* ************************************************************************** */

static int			_create_heredoc(
						const char *delim
						);

static void			_print_redirection_error(
						t_io_info *io_info
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
	size_t		i;
	int			fd;
	t_io_info	*info;

	if (list == NULL)
		return (false);
	info = list->io_infos;
	i = 0;
	while (i < list->used)
	{
		fd = _open_redirection(&info[i]);
		if (fd == -1)
			return (close(STDIN_FILENO), close(STDOUT_FILENO), true);
		if (info[i].io_type == IO_IN || info[i].io_type == IO_HEREDOC)
			dup2(fd, STDIN_FILENO);
		else
			dup2(fd, STDOUT_FILENO);
		close(fd);
		++i;
	}
	return (false);
}

/* ************************************************************************** */
/*                                                                            */
/* Helper implementation                                                      */
/*                                                                            */
/* ************************************************************************** */

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
	line = get_next_line(STDIN_FILENO);
	while (line)
	{
		if (ft_strncmp(delim, line, delim_length) == 0
			&& line + delim_length == (char *)u_get_end(line))
			break ;
		dprintf(fileno(f), "%s", line);
		free(line);
		line = get_next_line(STDIN_FILENO);
	}
	free(line);
	lseek(fileno(f), 0, SEEK_SET);
	fd = dup(fileno(f));
	fclose(f);
	return (fd);
}

static void	_print_redirection_error(
				t_io_info *io_info
				)
{
	dprintf(STDERR_FILENO, MS);
	if (io_info->io_type == IO_HEREDOC)
		dprintf(STDERR_FILENO, "Cannot create heredoc\n");
	else
		(dprintf(STDERR_FILENO, "%s: ", io_info->file), perror(""));
}

static int	_open_redirection(
				t_io_info *io_info
				)
{
	int	fd;

	if (io_info->io_type == IO_IN)
		fd = open(io_info->file, O_IN);
	else if (io_info->io_type == IO_OUT)
		fd = open(io_info->file, O_OT, 0666);
	else if (io_info->io_type == IO_APPEND)
		fd = open(io_info->file, O_AP, 0666);
	else
		fd = _create_heredoc(io_info->file);
	if (fd == -1)
		_print_redirection_error(io_info);
	return (fd);
}
