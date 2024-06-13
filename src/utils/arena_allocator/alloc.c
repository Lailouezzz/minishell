/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Antoine Massias <massias.antoine.pro@gm    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 16:43:36 by Antoine Mas       #+#    #+#             */
/*   Updated: 2024/06/13 20:13:05 by Antoine Mas      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file alloc.c
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

#include <libft.h>

/* ************************************************************************** */
/*                                                                            */
/* Helper prototypes                                                          */
/*                                                                            */
/* ************************************************************************** */

static struct s_arena_allocator_page	*_create_new_page(
											size_t size
											);

/* ************************************************************************** */
/*                                                                            */
/* Header implementation                                                      */
/*                                                                            */
/* ************************************************************************** */

void	*arena_allocator_alloc(
			t_arena_allocator *allocator,
			size_t size
			)
{
	struct s_arena_allocator_page	*new_page;
	char							*res;

	size += sizeof(size_t);
	if (allocator->current_page->remaining < size)
	{
		new_page = _create_new_page(size);
		if (new_page == NULL)
			return (NULL);
		allocator->current_page->next = new_page;
		allocator->current_page = new_page;
	}
	res = allocator->current_page->buffer + allocator->current_page->allocated;
	allocator->current_page->remaining -= size;
	allocator->current_page->allocated += size;
	*(size_t *)res = size - sizeof(size_t);
	return (res + sizeof(size_t));
}

void	*arena_allocator_realloc(
			t_arena_allocator *allocator,
			void *ptr,
			size_t new_size
			)
{
	void	*res;
	size_t	old_size;

	if (new_size == 0)
		return (NULL);
	res = arena_allocator_alloc(allocator, new_size);
	if (res == NULL)
		return (NULL);
	if (ptr == NULL)
		return (res);
	old_size = *((char *)ptr - sizeof(size_t));
	if (old_size < new_size)
		new_size = old_size;
	ft_memcpy(res, ptr, new_size);
	return (res);
}

/* ************************************************************************** */
/*                                                                            */
/* Helper implementation                                                      */
/*                                                                            */
/* ************************************************************************** */

static struct s_arena_allocator_page	*_create_new_page(
											size_t size
											)
{
	struct s_arena_allocator_page	*page;
	size_t							actual_size;

	actual_size = size + ARENA_ALLOC_MIN_SIZE - 1;
	actual_size = actual_size - actual_size % ARENA_ALLOC_MIN_SIZE;
	page = malloc(sizeof(*page) + actual_size * ARENA_ALLOC_MIN_SIZE);
	if (page == NULL)
		return (NULL);
	*page = (struct s_arena_allocator_page){
		.remaining = actual_size,
		.allocated = 0,
		.next = NULL,
	};
	return (page);
}
