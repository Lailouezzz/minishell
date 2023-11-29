/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-boud <ale-boud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 02:56:39 by ale-boud          #+#    #+#             */
/*   Updated: 2023/11/29 13:00:00 by ale-boud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file table.c
 * @author ale-boud (ale-boud@student.42.fr)
 * @brief The LR tables.
 * @date 2023-11-29
 * @copyright Copyright (c) 2023
 */

// ************************************************************************** //
// *                                                                        * //
// * Includes.                                                              * //
// *                                                                        * //
// ************************************************************************** //

#include "table.h"

// ************************************************************************** //
// *                                                                        * //
// * The LR tables.                                                         * //
// *                                                                        * //
// ************************************************************************** //

const t_lr_action	g_lr_table[STATE__COUNT][TOKEN__COUNT] = {
[0] = {
[TOKEN_WORD] = {ACTION_SHIFT, .data.shift_id = 1},
[TOKEN_IO] = {ACTION_ERROR, {}},
[TOKEN_END] = {ACTION_ERROR, {}},
},
[1] = {
[TOKEN_WORD] = {ACTION_REDUCE, .data.reduce_id = PROD_PROGNAME},
[TOKEN_IO] = {ACTION_REDUCE, .data.reduce_id = PROD_PROGNAME},
[TOKEN_END] = {ACTION_REDUCE, .data.reduce_id = PROD_PROGNAME},
},
[2] = {
[TOKEN_WORD] = {ACTION_SHIFT, .data.shift_id = 3},
[TOKEN_IO] = {ACTION_REDUCE, .data.reduce_id = PROD_COMMAND_SIMPLE__1},
[TOKEN_END] = {ACTION_REDUCE, .data.reduce_id = PROD_COMMAND_SIMPLE__1},
},
[3] = {
[TOKEN_WORD] = {ACTION_SHIFT, .data.shift_id = 3},
[TOKEN_IO] = {ACTION_REDUCE, .data.reduce_id = PROD_ARGS__1},
[TOKEN_END] = {ACTION_REDUCE, .data.reduce_id = PROD_ARGS__1},
},
[4] = {
[TOKEN_WORD] = {ACTION_ERROR, {}},
[TOKEN_IO] = {ACTION_REDUCE, .data.reduce_id = PROD_ARGS__2},
[TOKEN_END] = {ACTION_REDUCE, .data.reduce_id = PROD_ARGS__2},
},
[5] = {
[TOKEN_WORD] = {ACTION_ERROR, {}},
[TOKEN_IO] = {ACTION_REDUCE, .data.reduce_id = PROD_COMMAND_SIMPLE__2},
[TOKEN_END] = {ACTION_REDUCE, .data.reduce_id = PROD_COMMAND_SIMPLE__2},
},
[6] = {
[TOKEN_WORD] = {ACTION_ERROR, {}},
[TOKEN_IO] = {ACTION_SHIFT, .data.shift_id = 7},
[TOKEN_END] = {ACTION_REDUCE, .data.reduce_id = PROD_COMMAND__1},
},
[7] = {
[TOKEN_WORD] = {ACTION_SHIFT, .data.shift_id = 8},
[TOKEN_IO] = {ACTION_ERROR, {}},
[TOKEN_END] = {ACTION_ERROR, {}},
},
[8] = {
[TOKEN_WORD] = {ACTION_ERROR, {}},
[TOKEN_IO] = {ACTION_REDUCE, .data.reduce_id = PROD_IO_INFO},
[TOKEN_END] = {ACTION_REDUCE, .data.reduce_id = PROD_IO_INFO},
},
[9] = {
[TOKEN_WORD] = {ACTION_ERROR, {}},
[TOKEN_IO] = {ACTION_SHIFT, .data.shift_id = 7},
[TOKEN_END] = {ACTION_REDUCE, .data.reduce_id = PROD_COMMAND_IO__1},
},
[10] = {
[TOKEN_WORD] = {ACTION_ERROR, {}},
[TOKEN_IO] = {ACTION_ERROR, {}},
[TOKEN_END] = {ACTION_REDUCE, .data.reduce_id = PROD_COMMAND_IO__2},
},
[11] = {
[TOKEN_WORD] = {ACTION_ERROR, {}},
[TOKEN_IO] = {ACTION_ERROR, {}},
[TOKEN_END] = {ACTION_REDUCE, .data.reduce_id = PROD_COMMAND__2},
},
[12] = {
[TOKEN_WORD] = {ACTION_ERROR, {}},
[TOKEN_IO] = {ACTION_ERROR, {}},
[TOKEN_END] = {ACTION_ACCEPT, {}},
},
};

const t_lr_state_id	g_lr_goto_table[STATE__COUNT][PROD__COUNT] = {
[0] = {
[PROD_COMMAND__1] = 12,
[PROD_COMMAND__2] = 12,
[PROD_COMMAND_SIMPLE__1] = 6,
[PROD_COMMAND_SIMPLE__2] = 6,
[PROD_ARGS__1] = -1,
[PROD_ARGS__2] = -1,
[PROD_PROGNAME] = 2,
[PROD_COMMAND_IO__1] = -1,
[PROD_COMMAND_IO__2] = -1,
[PROD_IO_INFO] = -1,
},
[1] = {
[PROD_COMMAND__1] = -1,
[PROD_COMMAND__2] = -1,
[PROD_COMMAND_SIMPLE__1] = -1,
[PROD_COMMAND_SIMPLE__2] = -1,
[PROD_ARGS__1] = -1,
[PROD_ARGS__2] = -1,
[PROD_PROGNAME] = -1,
[PROD_COMMAND_IO__1] = -1,
[PROD_COMMAND_IO__2] = -1,
[PROD_IO_INFO] = -1,
},
[2] = {
[PROD_COMMAND__1] = -1,
[PROD_COMMAND__2] = -1,
[PROD_COMMAND_SIMPLE__1] = -1,
[PROD_COMMAND_SIMPLE__2] = -1,
[PROD_ARGS__1] = 5,
[PROD_ARGS__2] = 5,
[PROD_PROGNAME] = -1,
[PROD_COMMAND_IO__1] = -1,
[PROD_COMMAND_IO__2] = -1,
[PROD_IO_INFO] = -1,
},
[3] = {
[PROD_COMMAND__1] = -1,
[PROD_COMMAND__2] = -1,
[PROD_COMMAND_SIMPLE__1] = -1,
[PROD_COMMAND_SIMPLE__2] = -1,
[PROD_ARGS__1] = 4,
[PROD_ARGS__2] = 4,
[PROD_PROGNAME] = -1,
[PROD_COMMAND_IO__1] = -1,
[PROD_COMMAND_IO__2] = -1,
[PROD_IO_INFO] = -1,
},
[4] = {
[PROD_COMMAND__1] = -1,
[PROD_COMMAND__2] = -1,
[PROD_COMMAND_SIMPLE__1] = -1,
[PROD_COMMAND_SIMPLE__2] = -1,
[PROD_ARGS__1] = -1,
[PROD_ARGS__2] = -1,
[PROD_PROGNAME] = -1,
[PROD_COMMAND_IO__1] = -1,
[PROD_COMMAND_IO__2] = -1,
[PROD_IO_INFO] = -1,
},
[5] = {
[PROD_COMMAND__1] = -1,
[PROD_COMMAND__2] = -1,
[PROD_COMMAND_SIMPLE__1] = -1,
[PROD_COMMAND_SIMPLE__2] = -1,
[PROD_ARGS__1] = -1,
[PROD_ARGS__2] = -1,
[PROD_PROGNAME] = -1,
[PROD_COMMAND_IO__1] = -1,
[PROD_COMMAND_IO__2] = -1,
[PROD_IO_INFO] = -1,
},
[6] = {
[PROD_COMMAND__1] = -1,
[PROD_COMMAND__2] = -1,
[PROD_COMMAND_SIMPLE__1] = -1,
[PROD_COMMAND_SIMPLE__2] = -1,
[PROD_ARGS__1] = -1,
[PROD_ARGS__2] = -1,
[PROD_PROGNAME] = -1,
[PROD_COMMAND_IO__1] = 11,
[PROD_COMMAND_IO__2] = 11,
[PROD_IO_INFO] = 9,
},
[7] = {
[PROD_COMMAND__1] = -1,
[PROD_COMMAND__2] = -1,
[PROD_COMMAND_SIMPLE__1] = -1,
[PROD_COMMAND_SIMPLE__2] = -1,
[PROD_ARGS__1] = -1,
[PROD_ARGS__2] = -1,
[PROD_PROGNAME] = -1,
[PROD_COMMAND_IO__1] = -1,
[PROD_COMMAND_IO__2] = -1,
[PROD_IO_INFO] = -1,
},
[8] = {
[PROD_COMMAND__1] = -1,
[PROD_COMMAND__2] = -1,
[PROD_COMMAND_SIMPLE__1] = -1,
[PROD_COMMAND_SIMPLE__2] = -1,
[PROD_ARGS__1] = -1,
[PROD_ARGS__2] = -1,
[PROD_PROGNAME] = -1,
[PROD_COMMAND_IO__1] = -1,
[PROD_COMMAND_IO__2] = -1,
[PROD_IO_INFO] = -1,
},
[9] = {
[PROD_COMMAND__1] = -1,
[PROD_COMMAND__2] = -1,
[PROD_COMMAND_SIMPLE__1] = -1,
[PROD_COMMAND_SIMPLE__2] = -1,
[PROD_ARGS__1] = -1,
[PROD_ARGS__2] = -1,
[PROD_PROGNAME] = -1,
[PROD_COMMAND_IO__1] = 10,
[PROD_COMMAND_IO__2] = 10,
[PROD_IO_INFO] = 9,
},
[10] = {
[PROD_COMMAND__1] = -1,
[PROD_COMMAND__2] = -1,
[PROD_COMMAND_SIMPLE__1] = -1,
[PROD_COMMAND_SIMPLE__2] = -1,
[PROD_ARGS__1] = -1,
[PROD_ARGS__2] = -1,
[PROD_PROGNAME] = -1,
[PROD_COMMAND_IO__1] = -1,
[PROD_COMMAND_IO__2] = -1,
[PROD_IO_INFO] = -1,
},
[11] = {
[PROD_COMMAND__1] = -1,
[PROD_COMMAND__2] = -1,
[PROD_COMMAND_SIMPLE__1] = -1,
[PROD_COMMAND_SIMPLE__2] = -1,
[PROD_ARGS__1] = -1,
[PROD_ARGS__2] = -1,
[PROD_PROGNAME] = -1,
[PROD_COMMAND_IO__1] = -1,
[PROD_COMMAND_IO__2] = -1,
[PROD_IO_INFO] = -1,
},
[12] = {
[PROD_COMMAND__1] = -1,
[PROD_COMMAND__2] = -1,
[PROD_COMMAND_SIMPLE__1] = -1,
[PROD_COMMAND_SIMPLE__2] = -1,
[PROD_ARGS__1] = -1,
[PROD_ARGS__2] = -1,
[PROD_PROGNAME] = -1,
[PROD_COMMAND_IO__1] = -1,
[PROD_COMMAND_IO__2] = -1,
[PROD_IO_INFO] = -1,
},
};
