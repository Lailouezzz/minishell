/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena_allocator.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Antoine Massias <massias.antoine.pro@gm    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 14:12:11 by Antoine Mas       #+#    #+#             */
/*   Updated: 2024/06/13 14:43:45 by Antoine Mas      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file arena_allocator.c
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
/* Helper prototypes                                                          */
/*                                                                            */
/* ************************************************************************** */

static struct s_arena_allocator_page	*_create_new_page(
											size_t size
											);

static void								_destroy_page(
											struct s_arena_allocator_page *page
											);

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

void	*arena_allocator_alloc(
			t_arena_allocator *allocator,
			size_t size
			)
{
	struct s_arena_allocator	*new_page;
	void						*res;

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
	return (res);
}

void	arena_allocator_destroy(
			t_arena_allocator **allocator_ptr
			)
{
	if (allocator_ptr == NULL)
		return ;
	_destroy_page(&(*allocator_ptr)->first_page);
	*allocator_ptr = NULL;
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

	actual_size = (size + ARENA_ALLOC_MIN_SIZE - 1) / ARENA_ALLOC_MIN_SIZE;
	page = malloc(sizeof(*page) + actual_size);
	if (page == NULL)
		return (NULL);
	*page = (struct s_arena_allocator_page){
		.remaining = actual_size,
		.allocated = 0,
		.next = NULL,
	};
	return (page);
}

static void	_destroy_page(
				struct s_arena_allocator_page *page
				)
{
	if (page == NULL)
		return ;
	_destroy_page(page->next);
	free(page);
}
