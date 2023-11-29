/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-boud <ale-boud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 12:31:37 by ale-boud          #+#    #+#             */
/*   Updated: 2023/11/29 13:00:02 by ale-boud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file utils.c
 * @author ale-boud (ale-boud@student.42.fr)
 * @brief The helpers implementation.
 * @date 2023-11-29
 * @copyright Copyright (c) 2023
 */

// ************************************************************************** //
// *                                                                        * //
// * Includes.                                                              * //
// *                                                                        * //
// ************************************************************************** //

#include "utils.h"

// ************************************************************************** //
// *                                                                        * //
// * Header functions.                                                      * //
// *                                                                        * //
// ************************************************************************** //

void	*ft_realloc(
			void *p,
			size_t oldsize,
			size_t newsize
			)
{
	char	*newp;

	newp = malloc(newsize);
	if (newp == NULL)
	{
		free(p);
		return (NULL);
	}
	ft_memcpy(newp, p, oldsize);
	free(p);
	return (newp);
}

void	*ft_memcpy(
			void *dst,
			const void *src,
			size_t n
			)
{
	char	*pdst;
	char	*psrc;

	if (n == 0)
		return (dst);
	pdst = (char *)dst;
	psrc = (char *)src;
	while (n-- != 0)
	{
		pdst[n] = psrc[n];
	}
	return (dst);
}

int	ft_strlen(
		const char *str
		)
{
	int	k;

	k = 0;
	while (str[k] != '\0')
		++k;
	return (k);
}

char	*ft_strdup(
			const char *str
			)
{
	char	*s;

	s = malloc(ft_strlen(str) + 1);
	if (s == NULL)
		return (NULL);
	return (ft_memcpy(s, str, ft_strlen(str) + 1));
}
