/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena_allocator.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Antoine Massias <massias.antoine.pro@gm    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 14:00:19 by Antoine Mas       #+#    #+#             */
/*   Updated: 2024/06/13 14:33:40 by Antoine Mas      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file arena_allocator.h
 * @author Antoine Massias (amassias@student.42lehavre.fr)
 * @date 2024-06-13
 * @copyright Copyright (c) 2024
 */

#ifndef ARENA_ALLOCATOR_H
# define ARENA_ALLOCATOR_H

/* ************************************************************************** */
/*                                                                            */
/* Includes                                                                   */
/*                                                                            */
/* ************************************************************************** */

# include <stdlib.h>

/* ************************************************************************** */
/*                                                                            */
/* Defines                                                                    */
/*                                                                            */
/* ************************************************************************** */

# ifndef ARENA_ALLOC_MIN_SIZE
#  define ARENA_ALLOC_MIN_SIZE 4096
# endif

/* ************************************************************************** */
/*                                                                            */
/* Structures                                                                 */
/*                                                                            */
/* ************************************************************************** */

struct s_arena_allocator_page
{
	size_t							remaining;
	size_t							allocated;
	struct s_arena_allocator_page	*next;
	char							buffer[];
};

typedef struct s_arena_allocator
{
	struct s_arena_allocator_page	*current_page;
	struct s_arena_allocator_page	first_page;
}	t_arena_allocator;

/* ************************************************************************** */
/*                                                                            */
/* Header prototypes                                                          */
/*                                                                            */
/* ************************************************************************** */

t_arena_allocator	*arena_allocator_create(void);

void				*arena_allocator_alloc(
						t_arena_allocator *allocator,
						size_t size
						);

void				arena_allocator_destroy(
						t_arena_allocator **allocator_ptr
						);

#endif