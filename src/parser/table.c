/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-boud <ale-boud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 02:56:39 by ale-boud          #+#    #+#             */
/*   Updated: 2023/12/11 18:47:01 by ale-boud         ###   ########.fr       */
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

#include "parser/table.h"

// ************************************************************************** //
// *                                                                        * //
// * The LR tables.                                                         * //
// *                                                                        * //
// ************************************************************************** //

const t_lr_action	g_lr_table[STATE__COUNT][TOKEN__COUNT] = {
[0] = {
[TOKEN_WORD] = {ACTION_SHIFT, .data.shift_id = 24},
[TOKEN_IO] = {ACTION_SHIFT, .data.shift_id = 7},
[TOKEN_AND_OR] = {ACTION_ERROR, {}},
[TOKEN_PIPE] = {ACTION_ERROR, {}},
[TOKEN_OBRACKET] = {ACTION_SHIFT, .data.shift_id = 9},
[TOKEN_CBRACKET] = {ACTION_ERROR, {}},
[TOKEN_END] = {ACTION_ERROR, {}},
},
[1] = {
[TOKEN_WORD] = {ACTION_SHIFT, .data.shift_id = 5},
[TOKEN_IO] = {ACTION_SHIFT, .data.shift_id = 7},
[TOKEN_AND_OR] = {ACTION_REDUCE, .data.reduce_id = PROD_SIMPLE_COMMAND__1},
[TOKEN_PIPE] = {ACTION_REDUCE, .data.reduce_id = PROD_SIMPLE_COMMAND__1},
[TOKEN_OBRACKET] = {ACTION_ERROR, {}},
[TOKEN_CBRACKET] = {ACTION_REDUCE, .data.reduce_id = PROD_SIMPLE_COMMAND__1},
[TOKEN_END] = {ACTION_REDUCE, .data.reduce_id = PROD_SIMPLE_COMMAND__1},
},
[2] = {
[TOKEN_WORD] = {ACTION_REDUCE, .data.reduce_id = PROD_ARG_RED__IO},
[TOKEN_IO] = {ACTION_REDUCE, .data.reduce_id = PROD_ARG_RED__IO},
[TOKEN_AND_OR] = {ACTION_REDUCE, .data.reduce_id = PROD_ARG_RED__IO},
[TOKEN_PIPE] = {ACTION_REDUCE, .data.reduce_id = PROD_ARG_RED__IO},
[TOKEN_OBRACKET] = {ACTION_ERROR, {}},
[TOKEN_CBRACKET] = {ACTION_REDUCE, .data.reduce_id = PROD_ARG_RED__IO},
[TOKEN_END] = {ACTION_REDUCE, .data.reduce_id = PROD_ARG_RED__IO},
},
[3] = {
[TOKEN_WORD] = {ACTION_REDUCE, .data.reduce_id = PROD_ARG_RED_LIST__1},
[TOKEN_IO] = {ACTION_REDUCE, .data.reduce_id = PROD_ARG_RED_LIST__1},
[TOKEN_AND_OR] = {ACTION_REDUCE, .data.reduce_id = PROD_ARG_RED_LIST__1},
[TOKEN_PIPE] = {ACTION_REDUCE, .data.reduce_id = PROD_ARG_RED_LIST__1},
[TOKEN_OBRACKET] = {ACTION_ERROR, {}},
[TOKEN_CBRACKET] = {ACTION_REDUCE, .data.reduce_id = PROD_ARG_RED_LIST__1},
[TOKEN_END] = {ACTION_REDUCE, .data.reduce_id = PROD_ARG_RED_LIST__1},
},
[4] = {
[TOKEN_WORD] = {ACTION_SHIFT, .data.shift_id = 5},
[TOKEN_IO] = {ACTION_SHIFT, .data.shift_id = 7},
[TOKEN_AND_OR] = {ACTION_REDUCE, .data.reduce_id = PROD_SIMPLE_COMMAND__PNARL},
[TOKEN_PIPE] = {ACTION_REDUCE, .data.reduce_id = PROD_SIMPLE_COMMAND__PNARL},
[TOKEN_OBRACKET] = {ACTION_ERROR, {}},
[TOKEN_CBRACKET] = {ACTION_REDUCE,
	.data.reduce_id = PROD_SIMPLE_COMMAND__PNARL},
[TOKEN_END] = {ACTION_REDUCE, .data.reduce_id = PROD_SIMPLE_COMMAND__PNARL},
},
[5] = {
[TOKEN_WORD] = {ACTION_REDUCE, .data.reduce_id = PROD_ARG_RED__ARG},
[TOKEN_IO] = {ACTION_REDUCE, .data.reduce_id = PROD_ARG_RED__ARG},
[TOKEN_AND_OR] = {ACTION_REDUCE, .data.reduce_id = PROD_ARG_RED__ARG},
[TOKEN_PIPE] = {ACTION_REDUCE, .data.reduce_id = PROD_ARG_RED__ARG},
[TOKEN_OBRACKET] = {ACTION_ERROR, {}},
[TOKEN_CBRACKET] = {ACTION_REDUCE, .data.reduce_id = PROD_ARG_RED__ARG},
[TOKEN_END] = {ACTION_REDUCE, .data.reduce_id = PROD_ARG_RED__ARG},
},
[6] = {
[TOKEN_WORD] = {ACTION_REDUCE, .data.reduce_id = PROD_ARG_RED_LIST__2},
[TOKEN_IO] = {ACTION_REDUCE, .data.reduce_id = PROD_ARG_RED_LIST__2},
[TOKEN_AND_OR] = {ACTION_REDUCE, .data.reduce_id = PROD_ARG_RED_LIST__2},
[TOKEN_PIPE] = {ACTION_REDUCE, .data.reduce_id = PROD_ARG_RED_LIST__2},
[TOKEN_OBRACKET] = {ACTION_ERROR, {}},
[TOKEN_CBRACKET] = {ACTION_REDUCE, .data.reduce_id = PROD_ARG_RED_LIST__2},
[TOKEN_END] = {ACTION_REDUCE, .data.reduce_id = PROD_ARG_RED_LIST__2},
},
[7] = {
[TOKEN_WORD] = {ACTION_SHIFT, .data.shift_id = 8},
[TOKEN_IO] = {ACTION_ERROR, {}},
[TOKEN_AND_OR] = {ACTION_ERROR, {}},
[TOKEN_PIPE] = {ACTION_ERROR, {}},
[TOKEN_OBRACKET] = {ACTION_ERROR, {}},
[TOKEN_CBRACKET] = {ACTION_ERROR, {}},
[TOKEN_END] = {ACTION_ERROR, {}},
},
[8] = {
[TOKEN_WORD] = {ACTION_REDUCE, .data.reduce_id = PROD_IO_INFO},
[TOKEN_IO] = {ACTION_REDUCE, .data.reduce_id = PROD_IO_INFO},
[TOKEN_AND_OR] = {ACTION_REDUCE, .data.reduce_id = PROD_IO_INFO},
[TOKEN_PIPE] = {ACTION_REDUCE, .data.reduce_id = PROD_IO_INFO},
[TOKEN_OBRACKET] = {ACTION_ERROR, {}},
[TOKEN_CBRACKET] = {ACTION_REDUCE, .data.reduce_id = PROD_IO_INFO},
[TOKEN_END] = {ACTION_REDUCE, .data.reduce_id = PROD_IO_INFO},
},
[9] = {
[TOKEN_WORD] = {ACTION_SHIFT, .data.shift_id = 24},
[TOKEN_IO] = {ACTION_SHIFT, .data.shift_id = 7},
[TOKEN_AND_OR] = {ACTION_ERROR, {}},
[TOKEN_PIPE] = {ACTION_ERROR, {}},
[TOKEN_OBRACKET] = {ACTION_SHIFT, .data.shift_id = 9},
[TOKEN_CBRACKET] = {ACTION_ERROR, {}},
[TOKEN_END] = {ACTION_ERROR, {}},
},
[10] = {
[TOKEN_WORD] = {ACTION_ERROR, {}},
[TOKEN_IO] = {ACTION_ERROR, {}},
[TOKEN_AND_OR] = {ACTION_SHIFT, .data.shift_id = 12},
[TOKEN_PIPE] = {ACTION_ERROR, {}},
[TOKEN_OBRACKET] = {ACTION_ERROR, {}},
[TOKEN_CBRACKET] = {ACTION_SHIFT, .data.shift_id = 11},
[TOKEN_END] = {ACTION_ERROR, {}},
},
[11] = {
[TOKEN_WORD] = {ACTION_ERROR, {}},
[TOKEN_IO] = {ACTION_REDUCE, .data.reduce_id = PROD_SUBSHELL},
[TOKEN_AND_OR] = {ACTION_REDUCE, .data.reduce_id = PROD_SUBSHELL},
[TOKEN_PIPE] = {ACTION_REDUCE, .data.reduce_id = PROD_SUBSHELL},
[TOKEN_OBRACKET] = {ACTION_ERROR, {}},
[TOKEN_CBRACKET] = {ACTION_REDUCE, .data.reduce_id = PROD_SUBSHELL},
[TOKEN_END] = {ACTION_REDUCE, .data.reduce_id = PROD_SUBSHELL},
},
[12] = {
[TOKEN_WORD] = {ACTION_SHIFT, .data.shift_id = 24},
[TOKEN_IO] = {ACTION_SHIFT, .data.shift_id = 7},
[TOKEN_AND_OR] = {ACTION_SHIFT, .data.shift_id = 12},
[TOKEN_PIPE] = {ACTION_ERROR, {}},
[TOKEN_OBRACKET] = {ACTION_SHIFT, .data.shift_id = 9},
[TOKEN_CBRACKET] = {ACTION_ERROR, {}},
[TOKEN_END] = {ACTION_ERROR, {}},
},
[13] = {
[TOKEN_WORD] = {ACTION_ERROR, {}},
[TOKEN_IO] = {ACTION_ERROR, {}},
[TOKEN_AND_OR] = {ACTION_SHIFT, .data.shift_id = 12},
[TOKEN_PIPE] = {ACTION_ERROR, {}},
[TOKEN_OBRACKET] = {ACTION_ERROR, {}},
[TOKEN_CBRACKET] = {ACTION_ERROR, {}},
[TOKEN_END] = {ACTION_REDUCE, .data.reduce_id = PROD_COMMAND_LINE},
},
[14] = {
[TOKEN_WORD] = {ACTION_ERROR, {}},
[TOKEN_IO] = {ACTION_ERROR, {}},
[TOKEN_AND_OR] = {ACTION_REDUCE, .data.reduce_id = PROD_AND_OR__1},
[TOKEN_PIPE] = {ACTION_SHIFT, .data.shift_id = 15},
[TOKEN_OBRACKET] = {ACTION_ERROR, {}},
[TOKEN_CBRACKET] = {ACTION_REDUCE, .data.reduce_id = PROD_AND_OR__1},
[TOKEN_END] = {ACTION_REDUCE, .data.reduce_id = PROD_AND_OR__1},
},
[15] = {
[TOKEN_WORD] = {ACTION_SHIFT, .data.shift_id = 24},
[TOKEN_IO] = {ACTION_SHIFT, .data.shift_id = 7},
[TOKEN_AND_OR] = {ACTION_ERROR, {}},
[TOKEN_PIPE] = {ACTION_ERROR, {}},
[TOKEN_OBRACKET] = {ACTION_SHIFT, .data.shift_id = 9},
[TOKEN_CBRACKET] = {ACTION_ERROR, {}},
[TOKEN_END] = {ACTION_ERROR, {}},
},
[16] = {
[TOKEN_WORD] = {ACTION_ERROR, {}},
[TOKEN_IO] = {ACTION_ERROR, {}},
[TOKEN_AND_OR] = {ACTION_REDUCE, .data.reduce_id = PROD_PIPELINE__3},
[TOKEN_PIPE] = {ACTION_REDUCE, .data.reduce_id = PROD_PIPELINE__3},
[TOKEN_OBRACKET] = {ACTION_ERROR, {}},
[TOKEN_CBRACKET] = {ACTION_REDUCE, .data.reduce_id = PROD_PIPELINE__3},
[TOKEN_END] = {ACTION_REDUCE, .data.reduce_id = PROD_PIPELINE__3},
},
[17] = {
[TOKEN_WORD] = {ACTION_ERROR, {}},
[TOKEN_IO] = {ACTION_SHIFT, .data.shift_id = 7},
[TOKEN_AND_OR] = {ACTION_REDUCE, .data.reduce_id = PROD_COMMAND__SS1},
[TOKEN_PIPE] = {ACTION_REDUCE, .data.reduce_id = PROD_COMMAND__SS1},
[TOKEN_OBRACKET] = {ACTION_ERROR, {}},
[TOKEN_CBRACKET] = {ACTION_REDUCE, .data.reduce_id = PROD_COMMAND__SS1},
[TOKEN_END] = {ACTION_REDUCE, .data.reduce_id = PROD_COMMAND__SS1},
},
[18] = {
[TOKEN_WORD] = {ACTION_REDUCE, .data.reduce_id = PROD_REDIRECT_LIST__1},
[TOKEN_IO] = {ACTION_REDUCE, .data.reduce_id = PROD_REDIRECT_LIST__1},
[TOKEN_AND_OR] = {ACTION_REDUCE, .data.reduce_id = PROD_REDIRECT_LIST__1},
[TOKEN_PIPE] = {ACTION_REDUCE, .data.reduce_id = PROD_REDIRECT_LIST__1},
[TOKEN_OBRACKET] = {ACTION_ERROR, {}},
[TOKEN_CBRACKET] = {ACTION_REDUCE, .data.reduce_id = PROD_REDIRECT_LIST__1},
[TOKEN_END] = {ACTION_REDUCE, .data.reduce_id = PROD_REDIRECT_LIST__1},
},
[19] = {
[TOKEN_WORD] = {ACTION_ERROR, {}},
[TOKEN_IO] = {ACTION_SHIFT, .data.shift_id = 7},
[TOKEN_AND_OR] = {ACTION_REDUCE, .data.reduce_id = PROD_COMMAND__SS2},
[TOKEN_PIPE] = {ACTION_REDUCE, .data.reduce_id = PROD_COMMAND__SS2},
[TOKEN_OBRACKET] = {ACTION_ERROR, {}},
[TOKEN_CBRACKET] = {ACTION_REDUCE, .data.reduce_id = PROD_COMMAND__SS2},
[TOKEN_END] = {ACTION_REDUCE, .data.reduce_id = PROD_COMMAND__SS2},
},
[20] = {
[TOKEN_WORD] = {ACTION_REDUCE, .data.reduce_id = PROD_REDIRECT_LIST__2},
[TOKEN_IO] = {ACTION_REDUCE, .data.reduce_id = PROD_REDIRECT_LIST__2},
[TOKEN_AND_OR] = {ACTION_REDUCE, .data.reduce_id = PROD_REDIRECT_LIST__2},
[TOKEN_PIPE] = {ACTION_REDUCE, .data.reduce_id = PROD_REDIRECT_LIST__2},
[TOKEN_OBRACKET] = {ACTION_ERROR, {}},
[TOKEN_CBRACKET] = {ACTION_REDUCE, .data.reduce_id = PROD_REDIRECT_LIST__2},
[TOKEN_END] = {ACTION_REDUCE, .data.reduce_id = PROD_REDIRECT_LIST__2},
},
[21] = {
[TOKEN_WORD] = {ACTION_SHIFT, .data.shift_id = 5},
[TOKEN_IO] = {ACTION_SHIFT, .data.shift_id = 7},
[TOKEN_AND_OR] = {ACTION_REDUCE, .data.reduce_id = PROD_SIMPLE_COMMAND__3},
[TOKEN_PIPE] = {ACTION_REDUCE, .data.reduce_id = PROD_SIMPLE_COMMAND__3},
[TOKEN_OBRACKET] = {ACTION_ERROR, {}},
[TOKEN_CBRACKET] = {ACTION_REDUCE, .data.reduce_id = PROD_SIMPLE_COMMAND__3},
[TOKEN_END] = {ACTION_REDUCE, .data.reduce_id = PROD_SIMPLE_COMMAND__3},
},
[22] = {
[TOKEN_WORD] = {ACTION_SHIFT, .data.shift_id = 5},
[TOKEN_IO] = {ACTION_SHIFT, .data.shift_id = 7},
[TOKEN_AND_OR] = {ACTION_REDUCE, .data.reduce_id = PROD_SIMPLE_COMMAND__RLPN},
[TOKEN_PIPE] = {ACTION_REDUCE, .data.reduce_id = PROD_SIMPLE_COMMAND__RLPN},
[TOKEN_OBRACKET] = {ACTION_ERROR, {}},
[TOKEN_CBRACKET] = {ACTION_REDUCE, .data.reduce_id = PROD_SIMPLE_COMMAND__RLPN},
[TOKEN_END] = {ACTION_REDUCE, .data.reduce_id = PROD_SIMPLE_COMMAND__RLPN},
},
[23] = {
[TOKEN_WORD] = {ACTION_SHIFT, .data.shift_id = 24},
[TOKEN_IO] = {ACTION_SHIFT, .data.shift_id = 7},
[TOKEN_AND_OR] = {ACTION_ERROR, {}},
[TOKEN_PIPE] = {ACTION_ERROR, {}},
[TOKEN_OBRACKET] = {ACTION_ERROR, {}},
[TOKEN_CBRACKET] = {ACTION_ERROR, {}},
[TOKEN_END] = {ACTION_ERROR, {}},
},
[24] = {
[TOKEN_WORD] = {ACTION_REDUCE, .data.reduce_id = PROD_PROGNAME},
[TOKEN_IO] = {ACTION_REDUCE, .data.reduce_id = PROD_PROGNAME},
[TOKEN_AND_OR] = {ACTION_REDUCE, .data.reduce_id = PROD_PROGNAME},
[TOKEN_PIPE] = {ACTION_REDUCE, .data.reduce_id = PROD_PROGNAME},
[TOKEN_OBRACKET] = {ACTION_ERROR, {}},
[TOKEN_CBRACKET] = {ACTION_REDUCE, .data.reduce_id = PROD_PROGNAME},
[TOKEN_END] = {ACTION_REDUCE, .data.reduce_id = PROD_PROGNAME},
},
[25] = {
[TOKEN_WORD] = {ACTION_ERROR, {}},
[TOKEN_IO] = {ACTION_ERROR, {}},
[TOKEN_AND_OR] = {ACTION_REDUCE, .data.reduce_id = PROD_COMMAND__SC},
[TOKEN_PIPE] = {ACTION_REDUCE, .data.reduce_id = PROD_COMMAND__SC},
[TOKEN_OBRACKET] = {ACTION_ERROR, {}},
[TOKEN_CBRACKET] = {ACTION_REDUCE, .data.reduce_id = PROD_COMMAND__SC},
[TOKEN_END] = {ACTION_REDUCE, .data.reduce_id = PROD_COMMAND__SC},
},
[26] = {
[TOKEN_WORD] = {ACTION_ERROR, {}},
[TOKEN_IO] = {ACTION_ERROR, {}},
[TOKEN_AND_OR] = {ACTION_REDUCE, .data.reduce_id = PROD_PIPELINE__1},
[TOKEN_PIPE] = {ACTION_REDUCE, .data.reduce_id = PROD_PIPELINE__1},
[TOKEN_OBRACKET] = {ACTION_ERROR, {}},
[TOKEN_CBRACKET] = {ACTION_REDUCE, .data.reduce_id = PROD_PIPELINE__1},
[TOKEN_END] = {ACTION_REDUCE, .data.reduce_id = PROD_PIPELINE__1},
},
[27] = {
[TOKEN_WORD] = {ACTION_ERROR, {}},
[TOKEN_IO] = {ACTION_ERROR, {}},
[TOKEN_AND_OR] = {ACTION_REDUCE, .data.reduce_id = PROD_AND_OR__3},
[TOKEN_PIPE] = {ACTION_SHIFT, .data.shift_id = 15},
[TOKEN_OBRACKET] = {ACTION_ERROR, {}},
[TOKEN_CBRACKET] = {ACTION_REDUCE, .data.reduce_id = PROD_AND_OR__3},
[TOKEN_END] = {ACTION_REDUCE, .data.reduce_id = PROD_AND_OR__3},
},
[28] = {
[TOKEN_WORD] = {ACTION_ERROR, {}},
[TOKEN_IO] = {ACTION_ERROR, {}},
[TOKEN_AND_OR] = {ACTION_ERROR, {}},
[TOKEN_PIPE] = {ACTION_ERROR, {}},
[TOKEN_OBRACKET] = {ACTION_ERROR, {}},
[TOKEN_CBRACKET] = {ACTION_ERROR, {}},
[TOKEN_END] = {ACTION_ACCEPT, {}},
},
};

const t_lr_state_id	g_lr_goto_table[STATE__COUNT][PROD__COUNT] = {
[0] = {
[PROD_COMMAND_LINE] = 28,
[PROD_AND_OR__1] = 13,
[PROD_AND_OR__3] = 13,
[PROD_PIPELINE__1] = 14,
[PROD_PIPELINE__3] = 14,
[PROD_COMMAND__SS1] = 26,
[PROD_COMMAND__SS2] = 26,
[PROD_COMMAND__SC] = 26,
[PROD_SUBSHELL] = 17,
[PROD_SIMPLE_COMMAND__1] = 25,
[PROD_SIMPLE_COMMAND__RLPN] = 25,
[PROD_SIMPLE_COMMAND__PNARL] = 25,
[PROD_SIMPLE_COMMAND__3] = 25,
[PROD_REDIRECT_LIST__1] = 23,
[PROD_REDIRECT_LIST__2] = 23,
[PROD_IO_INFO] = 18,
[PROD_PROGNAME] = 1,
[PROD_ARG_RED_LIST__1] = -1,
[PROD_ARG_RED_LIST__2] = -1,
[PROD_ARG_RED__ARG] = -1,
[PROD_ARG_RED__IO] = -1,
},
[1] = {
[PROD_COMMAND_LINE] = -1,
[PROD_AND_OR__1] = -1,
[PROD_AND_OR__3] = -1,
[PROD_PIPELINE__1] = -1,
[PROD_PIPELINE__3] = -1,
[PROD_COMMAND__SS1] = -1,
[PROD_COMMAND__SS2] = -1,
[PROD_COMMAND__SC] = -1,
[PROD_SUBSHELL] = -1,
[PROD_SIMPLE_COMMAND__1] = -1,
[PROD_SIMPLE_COMMAND__RLPN] = -1,
[PROD_SIMPLE_COMMAND__PNARL] = -1,
[PROD_SIMPLE_COMMAND__3] = -1,
[PROD_REDIRECT_LIST__1] = -1,
[PROD_REDIRECT_LIST__2] = -1,
[PROD_IO_INFO] = 2,
[PROD_PROGNAME] = -1,
[PROD_ARG_RED_LIST__1] = 4,
[PROD_ARG_RED_LIST__2] = 4,
[PROD_ARG_RED__ARG] = 3,
[PROD_ARG_RED__IO] = 3,
},
[2] = {
[PROD_COMMAND_LINE] = -1,
[PROD_AND_OR__1] = -1,
[PROD_AND_OR__3] = -1,
[PROD_PIPELINE__1] = -1,
[PROD_PIPELINE__3] = -1,
[PROD_COMMAND__SS1] = -1,
[PROD_COMMAND__SS2] = -1,
[PROD_COMMAND__SC] = -1,
[PROD_SUBSHELL] = -1,
[PROD_SIMPLE_COMMAND__1] = -1,
[PROD_SIMPLE_COMMAND__RLPN] = -1,
[PROD_SIMPLE_COMMAND__PNARL] = -1,
[PROD_SIMPLE_COMMAND__3] = -1,
[PROD_REDIRECT_LIST__1] = -1,
[PROD_REDIRECT_LIST__2] = -1,
[PROD_IO_INFO] = -1,
[PROD_PROGNAME] = -1,
[PROD_ARG_RED_LIST__1] = -1,
[PROD_ARG_RED_LIST__2] = -1,
[PROD_ARG_RED__ARG] = -1,
[PROD_ARG_RED__IO] = -1,
},
[3] = {
[PROD_COMMAND_LINE] = -1,
[PROD_AND_OR__1] = -1,
[PROD_AND_OR__3] = -1,
[PROD_PIPELINE__1] = -1,
[PROD_PIPELINE__3] = -1,
[PROD_COMMAND__SS1] = -1,
[PROD_COMMAND__SS2] = -1,
[PROD_COMMAND__SC] = -1,
[PROD_SUBSHELL] = -1,
[PROD_SIMPLE_COMMAND__1] = -1,
[PROD_SIMPLE_COMMAND__RLPN] = -1,
[PROD_SIMPLE_COMMAND__PNARL] = -1,
[PROD_SIMPLE_COMMAND__3] = -1,
[PROD_REDIRECT_LIST__1] = -1,
[PROD_REDIRECT_LIST__2] = -1,
[PROD_IO_INFO] = -1,
[PROD_PROGNAME] = -1,
[PROD_ARG_RED_LIST__1] = -1,
[PROD_ARG_RED_LIST__2] = -1,
[PROD_ARG_RED__ARG] = -1,
[PROD_ARG_RED__IO] = -1,
},
[4] = {
[PROD_COMMAND_LINE] = -1,
[PROD_AND_OR__1] = -1,
[PROD_AND_OR__3] = -1,
[PROD_PIPELINE__1] = -1,
[PROD_PIPELINE__3] = -1,
[PROD_COMMAND__SS1] = -1,
[PROD_COMMAND__SS2] = -1,
[PROD_COMMAND__SC] = -1,
[PROD_SUBSHELL] = -1,
[PROD_SIMPLE_COMMAND__1] = -1,
[PROD_SIMPLE_COMMAND__RLPN] = -1,
[PROD_SIMPLE_COMMAND__PNARL] = -1,
[PROD_SIMPLE_COMMAND__3] = -1,
[PROD_REDIRECT_LIST__1] = -1,
[PROD_REDIRECT_LIST__2] = -1,
[PROD_IO_INFO] = 2,
[PROD_PROGNAME] = -1,
[PROD_ARG_RED_LIST__1] = -1,
[PROD_ARG_RED_LIST__2] = -1,
[PROD_ARG_RED__ARG] = 6,
[PROD_ARG_RED__IO] = 6,
},
[5] = {
[PROD_COMMAND_LINE] = -1,
[PROD_AND_OR__1] = -1,
[PROD_AND_OR__3] = -1,
[PROD_PIPELINE__1] = -1,
[PROD_PIPELINE__3] = -1,
[PROD_COMMAND__SS1] = -1,
[PROD_COMMAND__SS2] = -1,
[PROD_COMMAND__SC] = -1,
[PROD_SUBSHELL] = -1,
[PROD_SIMPLE_COMMAND__1] = -1,
[PROD_SIMPLE_COMMAND__RLPN] = -1,
[PROD_SIMPLE_COMMAND__PNARL] = -1,
[PROD_SIMPLE_COMMAND__3] = -1,
[PROD_REDIRECT_LIST__1] = -1,
[PROD_REDIRECT_LIST__2] = -1,
[PROD_IO_INFO] = -1,
[PROD_PROGNAME] = -1,
[PROD_ARG_RED_LIST__1] = -1,
[PROD_ARG_RED_LIST__2] = -1,
[PROD_ARG_RED__ARG] = -1,
[PROD_ARG_RED__IO] = -1,
},
[6] = {
[PROD_COMMAND_LINE] = -1,
[PROD_AND_OR__1] = -1,
[PROD_AND_OR__3] = -1,
[PROD_PIPELINE__1] = -1,
[PROD_PIPELINE__3] = -1,
[PROD_COMMAND__SS1] = -1,
[PROD_COMMAND__SS2] = -1,
[PROD_COMMAND__SC] = -1,
[PROD_SUBSHELL] = -1,
[PROD_SIMPLE_COMMAND__1] = -1,
[PROD_SIMPLE_COMMAND__RLPN] = -1,
[PROD_SIMPLE_COMMAND__PNARL] = -1,
[PROD_SIMPLE_COMMAND__3] = -1,
[PROD_REDIRECT_LIST__1] = -1,
[PROD_REDIRECT_LIST__2] = -1,
[PROD_IO_INFO] = -1,
[PROD_PROGNAME] = -1,
[PROD_ARG_RED_LIST__1] = -1,
[PROD_ARG_RED_LIST__2] = -1,
[PROD_ARG_RED__ARG] = -1,
[PROD_ARG_RED__IO] = -1,
},
[7] = {
[PROD_COMMAND_LINE] = -1,
[PROD_AND_OR__1] = -1,
[PROD_AND_OR__3] = -1,
[PROD_PIPELINE__1] = -1,
[PROD_PIPELINE__3] = -1,
[PROD_COMMAND__SS1] = -1,
[PROD_COMMAND__SS2] = -1,
[PROD_COMMAND__SC] = -1,
[PROD_SUBSHELL] = -1,
[PROD_SIMPLE_COMMAND__1] = -1,
[PROD_SIMPLE_COMMAND__RLPN] = -1,
[PROD_SIMPLE_COMMAND__PNARL] = -1,
[PROD_SIMPLE_COMMAND__3] = -1,
[PROD_REDIRECT_LIST__1] = -1,
[PROD_REDIRECT_LIST__2] = -1,
[PROD_IO_INFO] = -1,
[PROD_PROGNAME] = -1,
[PROD_ARG_RED_LIST__1] = -1,
[PROD_ARG_RED_LIST__2] = -1,
[PROD_ARG_RED__ARG] = -1,
[PROD_ARG_RED__IO] = -1,
},
[8] = {
[PROD_COMMAND_LINE] = -1,
[PROD_AND_OR__1] = -1,
[PROD_AND_OR__3] = -1,
[PROD_PIPELINE__1] = -1,
[PROD_PIPELINE__3] = -1,
[PROD_COMMAND__SS1] = -1,
[PROD_COMMAND__SS2] = -1,
[PROD_COMMAND__SC] = -1,
[PROD_SUBSHELL] = -1,
[PROD_SIMPLE_COMMAND__1] = -1,
[PROD_SIMPLE_COMMAND__RLPN] = -1,
[PROD_SIMPLE_COMMAND__PNARL] = -1,
[PROD_SIMPLE_COMMAND__3] = -1,
[PROD_REDIRECT_LIST__1] = -1,
[PROD_REDIRECT_LIST__2] = -1,
[PROD_IO_INFO] = -1,
[PROD_PROGNAME] = -1,
[PROD_ARG_RED_LIST__1] = -1,
[PROD_ARG_RED_LIST__2] = -1,
[PROD_ARG_RED__ARG] = -1,
[PROD_ARG_RED__IO] = -1,
},
[9] = {
[PROD_COMMAND_LINE] = -1,
[PROD_AND_OR__1] = 10,
[PROD_AND_OR__3] = 10,
[PROD_PIPELINE__1] = 14,
[PROD_PIPELINE__3] = 14,
[PROD_COMMAND__SS1] = 26,
[PROD_COMMAND__SS2] = 26,
[PROD_COMMAND__SC] = 26,
[PROD_SUBSHELL] = 17,
[PROD_SIMPLE_COMMAND__1] = 25,
[PROD_SIMPLE_COMMAND__RLPN] = 25,
[PROD_SIMPLE_COMMAND__PNARL] = 25,
[PROD_SIMPLE_COMMAND__3] = 25,
[PROD_REDIRECT_LIST__1] = 23,
[PROD_REDIRECT_LIST__2] = 23,
[PROD_IO_INFO] = 18,
[PROD_PROGNAME] = 1,
[PROD_ARG_RED_LIST__1] = -1,
[PROD_ARG_RED_LIST__2] = -1,
[PROD_ARG_RED__ARG] = -1,
[PROD_ARG_RED__IO] = -1,
},
[10] = {
[PROD_COMMAND_LINE] = -1,
[PROD_AND_OR__1] = -1,
[PROD_AND_OR__3] = -1,
[PROD_PIPELINE__1] = -1,
[PROD_PIPELINE__3] = -1,
[PROD_COMMAND__SS1] = -1,
[PROD_COMMAND__SS2] = -1,
[PROD_COMMAND__SC] = -1,
[PROD_SUBSHELL] = -1,
[PROD_SIMPLE_COMMAND__1] = -1,
[PROD_SIMPLE_COMMAND__RLPN] = -1,
[PROD_SIMPLE_COMMAND__PNARL] = -1,
[PROD_SIMPLE_COMMAND__3] = -1,
[PROD_REDIRECT_LIST__1] = -1,
[PROD_REDIRECT_LIST__2] = -1,
[PROD_IO_INFO] = -1,
[PROD_PROGNAME] = -1,
[PROD_ARG_RED_LIST__1] = -1,
[PROD_ARG_RED_LIST__2] = -1,
[PROD_ARG_RED__ARG] = -1,
[PROD_ARG_RED__IO] = -1,
},
[11] = {
[PROD_COMMAND_LINE] = -1,
[PROD_AND_OR__1] = -1,
[PROD_AND_OR__3] = -1,
[PROD_PIPELINE__1] = -1,
[PROD_PIPELINE__3] = -1,
[PROD_COMMAND__SS1] = -1,
[PROD_COMMAND__SS2] = -1,
[PROD_COMMAND__SC] = -1,
[PROD_SUBSHELL] = -1,
[PROD_SIMPLE_COMMAND__1] = -1,
[PROD_SIMPLE_COMMAND__RLPN] = -1,
[PROD_SIMPLE_COMMAND__PNARL] = -1,
[PROD_SIMPLE_COMMAND__3] = -1,
[PROD_REDIRECT_LIST__1] = -1,
[PROD_REDIRECT_LIST__2] = -1,
[PROD_IO_INFO] = -1,
[PROD_PROGNAME] = -1,
[PROD_ARG_RED_LIST__1] = -1,
[PROD_ARG_RED_LIST__2] = -1,
[PROD_ARG_RED__ARG] = -1,
[PROD_ARG_RED__IO] = -1,
},
[12] = {
[PROD_COMMAND_LINE] = -1,
[PROD_AND_OR__1] = -1,
[PROD_AND_OR__3] = -1,
[PROD_PIPELINE__1] = 27,
[PROD_PIPELINE__3] = 27,
[PROD_COMMAND__SS1] = 26,
[PROD_COMMAND__SS2] = 26,
[PROD_COMMAND__SC] = 26,
[PROD_SUBSHELL] = 17,
[PROD_SIMPLE_COMMAND__1] = 25,
[PROD_SIMPLE_COMMAND__RLPN] = 25,
[PROD_SIMPLE_COMMAND__PNARL] = 25,
[PROD_SIMPLE_COMMAND__3] = 25,
[PROD_REDIRECT_LIST__1] = 23,
[PROD_REDIRECT_LIST__2] = 23,
[PROD_IO_INFO] = 18,
[PROD_PROGNAME] = 1,
[PROD_ARG_RED_LIST__1] = -1,
[PROD_ARG_RED_LIST__2] = -1,
[PROD_ARG_RED__ARG] = -1,
[PROD_ARG_RED__IO] = -1,
},
[13] = {
[PROD_COMMAND_LINE] = -1,
[PROD_AND_OR__1] = -1,
[PROD_AND_OR__3] = -1,
[PROD_PIPELINE__1] = -1,
[PROD_PIPELINE__3] = -1,
[PROD_COMMAND__SS1] = -1,
[PROD_COMMAND__SS2] = -1,
[PROD_COMMAND__SC] = -1,
[PROD_SUBSHELL] = -1,
[PROD_SIMPLE_COMMAND__1] = -1,
[PROD_SIMPLE_COMMAND__RLPN] = -1,
[PROD_SIMPLE_COMMAND__PNARL] = -1,
[PROD_SIMPLE_COMMAND__3] = -1,
[PROD_REDIRECT_LIST__1] = -1,
[PROD_REDIRECT_LIST__2] = -1,
[PROD_IO_INFO] = -1,
[PROD_PROGNAME] = -1,
[PROD_ARG_RED_LIST__1] = -1,
[PROD_ARG_RED_LIST__2] = -1,
[PROD_ARG_RED__ARG] = -1,
[PROD_ARG_RED__IO] = -1,
},
[14] = {
[PROD_COMMAND_LINE] = -1,
[PROD_AND_OR__1] = -1,
[PROD_AND_OR__3] = -1,
[PROD_PIPELINE__1] = -1,
[PROD_PIPELINE__3] = -1,
[PROD_COMMAND__SS1] = -1,
[PROD_COMMAND__SS2] = -1,
[PROD_COMMAND__SC] = -1,
[PROD_SUBSHELL] = -1,
[PROD_SIMPLE_COMMAND__1] = -1,
[PROD_SIMPLE_COMMAND__RLPN] = -1,
[PROD_SIMPLE_COMMAND__PNARL] = -1,
[PROD_SIMPLE_COMMAND__3] = -1,
[PROD_REDIRECT_LIST__1] = -1,
[PROD_REDIRECT_LIST__2] = -1,
[PROD_IO_INFO] = -1,
[PROD_PROGNAME] = -1,
[PROD_ARG_RED_LIST__1] = -1,
[PROD_ARG_RED_LIST__2] = -1,
[PROD_ARG_RED__ARG] = -1,
[PROD_ARG_RED__IO] = -1,
},
[15] = {
[PROD_COMMAND_LINE] = -1,
[PROD_AND_OR__1] = -1,
[PROD_AND_OR__3] = -1,
[PROD_PIPELINE__1] = -1,
[PROD_PIPELINE__3] = -1,
[PROD_COMMAND__SS1] = 16,
[PROD_COMMAND__SS2] = 16,
[PROD_COMMAND__SC] = 16,
[PROD_SUBSHELL] = 17,
[PROD_SIMPLE_COMMAND__1] = 25,
[PROD_SIMPLE_COMMAND__RLPN] = 25,
[PROD_SIMPLE_COMMAND__PNARL] = 25,
[PROD_SIMPLE_COMMAND__3] = 25,
[PROD_REDIRECT_LIST__1] = 23,
[PROD_REDIRECT_LIST__2] = 23,
[PROD_IO_INFO] = 18,
[PROD_PROGNAME] = 1,
[PROD_ARG_RED_LIST__1] = -1,
[PROD_ARG_RED_LIST__2] = -1,
[PROD_ARG_RED__ARG] = -1,
[PROD_ARG_RED__IO] = -1,
},
[16] = {
[PROD_COMMAND_LINE] = -1,
[PROD_AND_OR__1] = -1,
[PROD_AND_OR__3] = -1,
[PROD_PIPELINE__1] = -1,
[PROD_PIPELINE__3] = -1,
[PROD_COMMAND__SS1] = -1,
[PROD_COMMAND__SS2] = -1,
[PROD_COMMAND__SC] = -1,
[PROD_SUBSHELL] = -1,
[PROD_SIMPLE_COMMAND__1] = -1,
[PROD_SIMPLE_COMMAND__RLPN] = -1,
[PROD_SIMPLE_COMMAND__PNARL] = -1,
[PROD_SIMPLE_COMMAND__3] = -1,
[PROD_REDIRECT_LIST__1] = -1,
[PROD_REDIRECT_LIST__2] = -1,
[PROD_IO_INFO] = -1,
[PROD_PROGNAME] = -1,
[PROD_ARG_RED_LIST__1] = -1,
[PROD_ARG_RED_LIST__2] = -1,
[PROD_ARG_RED__ARG] = -1,
[PROD_ARG_RED__IO] = -1,
},
[17] = {
[PROD_COMMAND_LINE] = -1,
[PROD_AND_OR__1] = -1,
[PROD_AND_OR__3] = -1,
[PROD_PIPELINE__1] = -1,
[PROD_PIPELINE__3] = -1,
[PROD_COMMAND__SS1] = -1,
[PROD_COMMAND__SS2] = -1,
[PROD_COMMAND__SC] = -1,
[PROD_SUBSHELL] = -1,
[PROD_SIMPLE_COMMAND__1] = -1,
[PROD_SIMPLE_COMMAND__RLPN] = -1,
[PROD_SIMPLE_COMMAND__PNARL] = -1,
[PROD_SIMPLE_COMMAND__3] = -1,
[PROD_REDIRECT_LIST__1] = 19,
[PROD_REDIRECT_LIST__2] = 19,
[PROD_IO_INFO] = 18,
[PROD_PROGNAME] = -1,
[PROD_ARG_RED_LIST__1] = -1,
[PROD_ARG_RED_LIST__2] = -1,
[PROD_ARG_RED__ARG] = -1,
[PROD_ARG_RED__IO] = -1,
},
[18] = {
[PROD_COMMAND_LINE] = -1,
[PROD_AND_OR__1] = -1,
[PROD_AND_OR__3] = -1,
[PROD_PIPELINE__1] = -1,
[PROD_PIPELINE__3] = -1,
[PROD_COMMAND__SS1] = -1,
[PROD_COMMAND__SS2] = -1,
[PROD_COMMAND__SC] = -1,
[PROD_SUBSHELL] = -1,
[PROD_SIMPLE_COMMAND__1] = -1,
[PROD_SIMPLE_COMMAND__RLPN] = -1,
[PROD_SIMPLE_COMMAND__PNARL] = -1,
[PROD_SIMPLE_COMMAND__3] = -1,
[PROD_REDIRECT_LIST__1] = -1,
[PROD_REDIRECT_LIST__2] = -1,
[PROD_IO_INFO] = -1,
[PROD_PROGNAME] = -1,
[PROD_ARG_RED_LIST__1] = -1,
[PROD_ARG_RED_LIST__2] = -1,
[PROD_ARG_RED__ARG] = -1,
[PROD_ARG_RED__IO] = -1,
},
[19] = {
[PROD_COMMAND_LINE] = -1,
[PROD_AND_OR__1] = -1,
[PROD_AND_OR__3] = -1,
[PROD_PIPELINE__1] = -1,
[PROD_PIPELINE__3] = -1,
[PROD_COMMAND__SS1] = -1,
[PROD_COMMAND__SS2] = -1,
[PROD_COMMAND__SC] = -1,
[PROD_SUBSHELL] = -1,
[PROD_SIMPLE_COMMAND__1] = -1,
[PROD_SIMPLE_COMMAND__RLPN] = -1,
[PROD_SIMPLE_COMMAND__PNARL] = -1,
[PROD_SIMPLE_COMMAND__3] = -1,
[PROD_REDIRECT_LIST__1] = -1,
[PROD_REDIRECT_LIST__2] = -1,
[PROD_IO_INFO] = 20,
[PROD_PROGNAME] = -1,
[PROD_ARG_RED_LIST__1] = -1,
[PROD_ARG_RED_LIST__2] = -1,
[PROD_ARG_RED__ARG] = -1,
[PROD_ARG_RED__IO] = -1,
},
[20] = {
[PROD_COMMAND_LINE] = -1,
[PROD_AND_OR__1] = -1,
[PROD_AND_OR__3] = -1,
[PROD_PIPELINE__1] = -1,
[PROD_PIPELINE__3] = -1,
[PROD_COMMAND__SS1] = -1,
[PROD_COMMAND__SS2] = -1,
[PROD_COMMAND__SC] = -1,
[PROD_SUBSHELL] = -1,
[PROD_SIMPLE_COMMAND__1] = -1,
[PROD_SIMPLE_COMMAND__RLPN] = -1,
[PROD_SIMPLE_COMMAND__PNARL] = -1,
[PROD_SIMPLE_COMMAND__3] = -1,
[PROD_REDIRECT_LIST__1] = -1,
[PROD_REDIRECT_LIST__2] = -1,
[PROD_IO_INFO] = -1,
[PROD_PROGNAME] = -1,
[PROD_ARG_RED_LIST__1] = -1,
[PROD_ARG_RED_LIST__2] = -1,
[PROD_ARG_RED__ARG] = -1,
[PROD_ARG_RED__IO] = -1,
},
[21] = {
[PROD_COMMAND_LINE] = -1,
[PROD_AND_OR__1] = -1,
[PROD_AND_OR__3] = -1,
[PROD_PIPELINE__1] = -1,
[PROD_PIPELINE__3] = -1,
[PROD_COMMAND__SS1] = -1,
[PROD_COMMAND__SS2] = -1,
[PROD_COMMAND__SC] = -1,
[PROD_SUBSHELL] = -1,
[PROD_SIMPLE_COMMAND__1] = -1,
[PROD_SIMPLE_COMMAND__RLPN] = -1,
[PROD_SIMPLE_COMMAND__PNARL] = -1,
[PROD_SIMPLE_COMMAND__3] = -1,
[PROD_REDIRECT_LIST__1] = -1,
[PROD_REDIRECT_LIST__2] = -1,
[PROD_IO_INFO] = 2,
[PROD_PROGNAME] = -1,
[PROD_ARG_RED_LIST__1] = -1,
[PROD_ARG_RED_LIST__2] = -1,
[PROD_ARG_RED__ARG] = 6,
[PROD_ARG_RED__IO] = 6,
},
[22] = {
[PROD_COMMAND_LINE] = -1,
[PROD_AND_OR__1] = -1,
[PROD_AND_OR__3] = -1,
[PROD_PIPELINE__1] = -1,
[PROD_PIPELINE__3] = -1,
[PROD_COMMAND__SS1] = -1,
[PROD_COMMAND__SS2] = -1,
[PROD_COMMAND__SC] = -1,
[PROD_SUBSHELL] = -1,
[PROD_SIMPLE_COMMAND__1] = -1,
[PROD_SIMPLE_COMMAND__RLPN] = -1,
[PROD_SIMPLE_COMMAND__PNARL] = -1,
[PROD_SIMPLE_COMMAND__3] = -1,
[PROD_REDIRECT_LIST__1] = -1,
[PROD_REDIRECT_LIST__2] = -1,
[PROD_IO_INFO] = 2,
[PROD_PROGNAME] = -1,
[PROD_ARG_RED_LIST__1] = 21,
[PROD_ARG_RED_LIST__2] = 21,
[PROD_ARG_RED__ARG] = 3,
[PROD_ARG_RED__IO] = 3,
},
[23] = {
[PROD_COMMAND_LINE] = -1,
[PROD_AND_OR__1] = -1,
[PROD_AND_OR__3] = -1,
[PROD_PIPELINE__1] = -1,
[PROD_PIPELINE__3] = -1,
[PROD_COMMAND__SS1] = -1,
[PROD_COMMAND__SS2] = -1,
[PROD_COMMAND__SC] = -1,
[PROD_SUBSHELL] = -1,
[PROD_SIMPLE_COMMAND__1] = -1,
[PROD_SIMPLE_COMMAND__RLPN] = -1,
[PROD_SIMPLE_COMMAND__PNARL] = -1,
[PROD_SIMPLE_COMMAND__3] = -1,
[PROD_REDIRECT_LIST__1] = -1,
[PROD_REDIRECT_LIST__2] = -1,
[PROD_IO_INFO] = 20,
[PROD_PROGNAME] = 22,
[PROD_ARG_RED_LIST__1] = -1,
[PROD_ARG_RED_LIST__2] = -1,
[PROD_ARG_RED__ARG] = -1,
[PROD_ARG_RED__IO] = -1,
},
[24] = {
[PROD_COMMAND_LINE] = -1,
[PROD_AND_OR__1] = -1,
[PROD_AND_OR__3] = -1,
[PROD_PIPELINE__1] = -1,
[PROD_PIPELINE__3] = -1,
[PROD_COMMAND__SS1] = -1,
[PROD_COMMAND__SS2] = -1,
[PROD_COMMAND__SC] = -1,
[PROD_SUBSHELL] = -1,
[PROD_SIMPLE_COMMAND__1] = -1,
[PROD_SIMPLE_COMMAND__RLPN] = -1,
[PROD_SIMPLE_COMMAND__PNARL] = -1,
[PROD_SIMPLE_COMMAND__3] = -1,
[PROD_REDIRECT_LIST__1] = -1,
[PROD_REDIRECT_LIST__2] = -1,
[PROD_IO_INFO] = -1,
[PROD_PROGNAME] = -1,
[PROD_ARG_RED_LIST__1] = -1,
[PROD_ARG_RED_LIST__2] = -1,
[PROD_ARG_RED__ARG] = -1,
[PROD_ARG_RED__IO] = -1,
},
[25] = {
[PROD_COMMAND_LINE] = -1,
[PROD_AND_OR__1] = -1,
[PROD_AND_OR__3] = -1,
[PROD_PIPELINE__1] = -1,
[PROD_PIPELINE__3] = -1,
[PROD_COMMAND__SS1] = -1,
[PROD_COMMAND__SS2] = -1,
[PROD_COMMAND__SC] = -1,
[PROD_SUBSHELL] = -1,
[PROD_SIMPLE_COMMAND__1] = -1,
[PROD_SIMPLE_COMMAND__RLPN] = -1,
[PROD_SIMPLE_COMMAND__PNARL] = -1,
[PROD_SIMPLE_COMMAND__3] = -1,
[PROD_REDIRECT_LIST__1] = -1,
[PROD_REDIRECT_LIST__2] = -1,
[PROD_IO_INFO] = -1,
[PROD_PROGNAME] = -1,
[PROD_ARG_RED_LIST__1] = -1,
[PROD_ARG_RED_LIST__2] = -1,
[PROD_ARG_RED__ARG] = -1,
[PROD_ARG_RED__IO] = -1,
},
[26] = {
[PROD_COMMAND_LINE] = -1,
[PROD_AND_OR__1] = -1,
[PROD_AND_OR__3] = -1,
[PROD_PIPELINE__1] = -1,
[PROD_PIPELINE__3] = -1,
[PROD_COMMAND__SS1] = -1,
[PROD_COMMAND__SS2] = -1,
[PROD_COMMAND__SC] = -1,
[PROD_SUBSHELL] = -1,
[PROD_SIMPLE_COMMAND__1] = -1,
[PROD_SIMPLE_COMMAND__RLPN] = -1,
[PROD_SIMPLE_COMMAND__PNARL] = -1,
[PROD_SIMPLE_COMMAND__3] = -1,
[PROD_REDIRECT_LIST__1] = -1,
[PROD_REDIRECT_LIST__2] = -1,
[PROD_IO_INFO] = -1,
[PROD_PROGNAME] = -1,
[PROD_ARG_RED_LIST__1] = -1,
[PROD_ARG_RED_LIST__2] = -1,
[PROD_ARG_RED__ARG] = -1,
[PROD_ARG_RED__IO] = -1,
},
[27] = {
[PROD_COMMAND_LINE] = -1,
[PROD_AND_OR__1] = -1,
[PROD_AND_OR__3] = -1,
[PROD_PIPELINE__1] = -1,
[PROD_PIPELINE__3] = -1,
[PROD_COMMAND__SS1] = -1,
[PROD_COMMAND__SS2] = -1,
[PROD_COMMAND__SC] = -1,
[PROD_SUBSHELL] = -1,
[PROD_SIMPLE_COMMAND__1] = -1,
[PROD_SIMPLE_COMMAND__RLPN] = -1,
[PROD_SIMPLE_COMMAND__PNARL] = -1,
[PROD_SIMPLE_COMMAND__3] = -1,
[PROD_REDIRECT_LIST__1] = -1,
[PROD_REDIRECT_LIST__2] = -1,
[PROD_IO_INFO] = -1,
[PROD_PROGNAME] = -1,
[PROD_ARG_RED_LIST__1] = -1,
[PROD_ARG_RED_LIST__2] = -1,
[PROD_ARG_RED__ARG] = -1,
[PROD_ARG_RED__IO] = -1,
},
};