/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Antoine Massias <massias.antoine.pro@gm    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 16:42:56 by Antoine Mas       #+#    #+#             */
/*   Updated: 2024/06/13 16:43:24 by Antoine Mas      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file create.c
 * @author Antoine Massias (amassias@student.42lehavre.fr)
 * @date 2024-06-13
 * @copyright Copyright (c) 2024
 */

/* ************************************************************************** */
/*                                                                            */
/* Includes                                                                   */
/*                                                                            */
/* ************************************************************************** */

#include "utils/arena_allocator.h"

/* ************************************************************************** */
/*                                                                            */
/* Header implementation                                                      */
/*                                                                            */
/* ************************************************************************** */

t_arena_allocator	*arena_allocator_create(void)
{
	t_arena_allocator	*allocator;

	allocator = malloc(sizeof(t_arena_allocator) + ARENA_ALLOC_MIN_SIZE);
	if (allocator == NULL)
		return (NULL);
	*allocator = (t_arena_allocator){
		.current_page = &allocator->first_page,
		.first_page.remaining = ARENA_ALLOC_MIN_SIZE,
		.first_page.allocated = 0,
		.first_page.next = NULL
	};
	return (allocator);
}
