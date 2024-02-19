/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_data.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amassias <amassias@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 17:59:11 by amassias          #+#    #+#             */
/*   Updated: 2024/02/15 18:10:23 by amassias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file builtins_data.c
 * @author Antoine Massias (amassias@student.42lehavre.fr)
 * @date 2024-02-15
 * @copyright Copyright (c) 2024
 */

/* ************************************************************************** */
/*                                                                            */
/* Includes                                                                   */
/*                                                                            */
/* ************************************************************************** */

#include "core/builtins.h"

/* ************************************************************************** */
/*                                                                            */
/* Global variables                                                           */
/*                                                                            */
/* ************************************************************************** */

const t_builtin_entry	g_builtins[BUILTIN_COUNT] = {
[BUILTIN_ECHO] = {
	.name = "echo",
	.fun = builtin_echo
},
[BUILTIN_CD] = {
	.name = "cd",
	.fun = builtin_cd
},
[BUILTIN_PWD] = {
	.name = "pwd",
	.fun = builtin_pwd
},
[BUILTIN_EXPORT] = {
	.name = "export",
	.fun = builtin_export
},
[BUILTIN_UNSET] = {
	.name = "unset",
	.fun = builtin_unset
},
[BUILTIN_ENV] = {
	.name = "env",
	.fun = builtin_env
},
[BUILTIN_EXIT] = {
	.name = "exit",
	.fun = builtin_exit
},
};