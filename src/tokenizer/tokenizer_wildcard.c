/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_wildcard.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-boud <ale-boud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 15:41:33 by ale-boud          #+#    #+#             */
/*   Updated: 2024/03/11 17:06:53 by ale-boud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file tokenizer_wildcard.c
 * @author ale-boud (ale-boud@student.42.fr)
 * @brief Wildcard functions.
 * @date 2024-03-11
 * @copyright Copyright (c) 2024
 */

// ************************************************************************** //
// *                                                                        * //
// * Includes.                                                              * //
// *                                                                        * //
// ************************************************************************** //

#include <errno.h>
#include <dirent.h>

#include <libft.h>

#include "tokenizer/tokenizer.h"

// ************************************************************************** //
// *                                                                        * //
// * Helper prototype.                                                      * //
// *                                                                        * //
// ************************************************************************** //

static t_ms_error	_state_wildcard_fill(
						t_lr_token_list *lrtoks,
						t_int_token *int_token,
						DIR *dir
						);

// ************************************************************************** //
// *                                                                        * //
// * Header functions.                                                      * //
// *                                                                        * //
// ************************************************************************** //

int	_token_cmp_word(
		void *p1,
		void *p2)
{
	const char	*s1 = ((t_lr_token *)p1)->data.word;
	const char	*s2 = ((t_lr_token *)p2)->data.word;

	while (ft_tolower(*s1) == ft_tolower(*s2) && *s1 != '\0' && *s2 != '\0')
	{
		++s1;
		++s2;
	}
	return (ft_tolower(*s1) - ft_tolower(*s2));
}

t_ms_error	_state_wildcard(
				t_lr_token_list *lrtoks,
				t_int_token *int_token
				)
{
	char *const			cwd = getcwd(NULL, 0);
	DIR					*dir;

	if (cwd == NULL)
		return (MS_BAD_ALLOC);
	dir = opendir(cwd);
	free(cwd);
	if (dir == NULL)
		return (MS_FATAL);
	return (_state_wildcard_fill(lrtoks, int_token, dir));
}

// ************************************************************************** //
// *                                                                        * //
// * Helper implementation.                                                 * //
// *                                                                        * //
// ************************************************************************** //

static t_ms_error	_state_wildcard_fill(
						t_lr_token_list *lrtoks,
						t_int_token *int_token,
						DIR *dir
						)
{
	struct dirent	*ent;
	t_lr_token		lrtok;

	(void)(int_token);
	errno = 0;
	ent = readdir(dir);
	while (ent != NULL && errno == 0)
	{
		if (*ent->d_name != '.')
		{
			if (_token_gen_word(&lrtok, ft_strdup(ent->d_name))
				|| lrtoks_pushback(lrtoks, &lrtok) != MS_OK)
				return (closedir(dir), MS_FATAL);
		}
		errno = 0;
		ent = readdir(dir);
	}
	closedir(dir);
	if (errno != 0)
		return (MS_FATAL);
	ft_qsort(lrtoks->lrtoks, lrtoks->used, sizeof(*lrtoks->lrtoks),
		_token_cmp_word);
	return (MS_OK);
}
