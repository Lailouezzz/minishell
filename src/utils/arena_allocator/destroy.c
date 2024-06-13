/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Antoine Massias <massias.antoine.pro@gm    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 16:44:46 by Antoine Mas       #+#    #+#             */
/*   Updated: 2024/06/13 16:45:21 by Antoine Mas      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file destroy.c
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

static void	_destroy_page(
				struct s_arena_allocator_page *page
				);

/* ************************************************************************** */
/*                                                                            */
/* Header implementation                                                      */
/*                                                                            */
/* ************************************************************************** */

void	arena_allocator_destroy(
			t_arena_allocator **allocator_ptr
			)
{
	if (allocator_ptr == NULL)
		return ;
	_destroy_page((*allocator_ptr)->first_page.next);
	free(*allocator_ptr);
	*allocator_ptr = NULL;
}

/* ************************************************************************** */
/*                                                                            */
/* Helper implementation                                                      */
/*                                                                            */
/* ************************************************************************** */

static void	_destroy_page(
				struct s_arena_allocator_page *page
				)
{
	if (page == NULL)
		return ;
	_destroy_page(page->next);
	free(page);
}
