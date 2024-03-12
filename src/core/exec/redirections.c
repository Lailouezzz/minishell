/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amassias <amassias@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 16:30:48 by amassias          #+#    #+#             */
/*   Updated: 2024/03/12 20:13:56 by amassias         ###   ########.fr       */
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

static void			_close_all(
						const int fds[2]
						);

static void			_swap_fd(
						int new_fd,
						int *fd
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
	const int	x[2] = {-1, -1};
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
			return (_close_all(x), true);
		if (info[i].io_type == IO_IN || info[i].io_type == IO_HEREDOC)
			_swap_fd(fd, (int *)&x[STDIN]);
		else
			_swap_fd(fd, (int *)&x[STDOUT]);
		++i;
	}
	if (x[STDOUT] != -1 && dup2(x[STDOUT], STDOUT_FILENO) == -1)
		return (_close_all(x), true);
	if (x[STDIN] != -1 && dup2(x[STDIN], STDIN_FILENO) == -1)
		return (_close_all(x), true);
	return ((void)(x[0] >= 0 && close(x[0])), x[1] >= 0 && close(x[1]), false);
}

/* ************************************************************************** */
/*                                                                            */
/* Helper implementation                                                      */
/*                                                                            */
/* ************************************************************************** */

static void	_close_all(
				const int fds[2]
				)
{
	if (fds[STDIN] >= 0)
		close(fds[STDIN]);
	if (fds[STDOUT] >= 0)
		close(fds[STDOUT]);
	(close(STDIN_FILENO), close(STDOUT_FILENO));
}

static void	_swap_fd(
				int new_fd,
				int *fd
				)
{
	if (*fd >= 0)
		close(*fd);
	*fd = new_fd;
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
		fd = io_info->fd;
	if (fd != -1)
		return (fd);
	dprintf(STDERR_FILENO, MS);
	if (io_info->io_type == IO_HEREDOC)
		dprintf(STDERR_FILENO, "Cannot create heredoc\n");
	else
		perror(io_info->file);
	return (-1);
}
