/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amassias <amassias@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 17:57:29 by amassias          #+#    #+#             */
/*   Updated: 2024/03/11 18:39:45 by amassias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file builtins.h
 * @author Antoine Massias (amassias@student.42lehavre.fr)
 * @date 2024-02-15
 * @copyright Copyright (c) 2024
 */

#ifndef BUILTINS_H
# define BUILTINS_H

/* ************************************************************************** */
/*                                                                            */
/* Includes                                                                   */
/*                                                                            */
/* ************************************************************************** */

# include "core/exec.h"

/* ************************************************************************** */
/*                                                                            */
/* Enums                                                                      */
/*                                                                            */
/* ************************************************************************** */

enum e_builtins
{
	BUILTIN_ECHO,
	BUILTIN_CD,
	BUILTIN_PWD,
	BUILTIN_EXPORT,
	BUILTIN_UNSET,
	BUILTIN_ENV,
	BUILTIN_EXIT,
	BUILTIN_COUNT
};

/* ************************************************************************** */
/*                                                                            */
/* Structures                                                                 */
/*                                                                            */
/* ************************************************************************** */

struct s_builtin_entry
{
	const char	*name;
	t_ms_error	(*fun)(t_exec_ctx *, char **, char **);
};

/* ************************************************************************** */
/*                                                                            */
/* Types                                                                      */
/*                                                                            */
/* ************************************************************************** */

typedef t_ms_error				(*t_builtin)(t_exec_ctx *, char **, char **);
typedef struct s_builtin_entry	t_builtin_entry;

/* ************************************************************************** */
/*                                                                            */
/* Global variables                                                           */
/*                                                                            */
/* ************************************************************************** */

extern const t_builtin_entry	g_builtins[BUILTIN_COUNT];

/* ************************************************************************** */
/*                                                                            */
/* Header protoypes                                                           */
/*                                                                            */
/* ************************************************************************** */

t_ms_error	builtin_echo(
				t_exec_ctx *ctx,
				char **argv,
				char **envp
				);

t_ms_error	builtin_cd(
				t_exec_ctx *ctx,
				char **argv,
				char **envp
				);

t_ms_error	builtin_pwd(
				t_exec_ctx *ctx,
				char **argv,
				char **envp
				);

t_ms_error	builtin_export(
				t_exec_ctx *ctx,
				char **argv,
				char **envp
				);

t_ms_error	builtin_unset(
				t_exec_ctx *ctx,
				char **argv,
				char **envp
				);

t_ms_error	builtin_env(
				t_exec_ctx *ctx,
				char **argv,
				char **envp
				);

t_ms_error	builtin_exit(
				t_exec_ctx *ctx,
				char **argv,
				char **envp
				);

#endif
