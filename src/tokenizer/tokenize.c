/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-boud <ale-boud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 15:22:16 by ale-boud          #+#    #+#             */
/*   Updated: 2024/02/13 17:21:36 by ale-boud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file tokenize.c
 * @author ale-boud (ale-boud@student.42lehavre.fr)
 * @brief The tokenize implementation.
 * @date 2023-11-30
 * @copyright Copyright (c) 2023
 */

// ************************************************************************** //
// *                                                                        * //
// * Includes.                                                              * //
// *                                                                        * //
// ************************************************************************** //

#include "tokenizer/tokenizer.h"

#include <libft.h>

// ************************************************************************** //
// *                                                                        * //
// * Helper function definition.                                            * //
// *                                                                        * //
// ************************************************************************** //

static int			ft_ismeta(
						char c
						);

static const char	*_expand_dollar(
						const char **start
						);

static t_ms_error	_flush_word_read(
						t_lr_token_list *lrtoks,
						t_int_token *int_token
						);

// ************************************************************************** //
// *                                                                        * //
// * States function prototypes.                                            * //
// *                                                                        * //
// ************************************************************************** //

static t_ms_error	_state_dollar(
						t_lr_token_list *lrtoks,
						t_int_token *int_token
						);

static t_ms_error	_state_dollar_quoted(
						t_lr_token_list *lrtoks,
						t_int_token *int_token
						);

static t_ms_error	_state_initial(
						t_lr_token_list *lrtoks,
						t_int_token *int_token
						);

static t_ms_error	_state_out(
						t_lr_token_list *lrtoks,
						t_int_token *int_token
						);

static t_ms_error	_state_in(
						t_lr_token_list *lrtoks,
						t_int_token *int_token
						);

static t_ms_error	_state_pipe_or(
						t_lr_token_list *lrtoks,
						t_int_token *int_token
						);

static t_ms_error	_state_and(
						t_lr_token_list *lrtoks,
						t_int_token *int_token
						);

static t_ms_error	_state_word(
						t_lr_token_list *lrtoks,
						t_int_token *int_token
						);

static t_ms_error	_state_quote(
						t_lr_token_list *lrtoks,
						t_int_token *int_token
						);

static t_ms_error	_state_doublequote(
						t_lr_token_list *lrtoks,
						t_int_token *int_token
						);

// ************************************************************************** //
// *                                                                        * //
// * Header functions.                                                      * //
// *                                                                        * //
// ************************************************************************** //

t_ms_error	tokenize(
				t_lr_token_list *lrtoks,
				const char **start
				)
{
	t_int_token	int_token;
	int			r;

	r = lrtoks_init(lrtoks);
	if (r != MS_OK)
		return (r);
	int_token.cur = *start;
	int_token.word_read.str = NULL;
	while (ft_isspace(*int_token.cur) && *int_token.cur != '\0')
		++int_token.cur;
	r = _state_initial(lrtoks, &int_token);
	if (r)
	{
		lrtoks_destroy(lrtoks);
		dyn_str_destroy(&int_token.word_read);
	}
	*start = int_token.cur;
	return (r);
}

// ************************************************************************** //
// *                                                                        * //
// * Helper function implementation.                                        * //
// *                                                                        * //
// ************************************************************************** //

static int	ft_ismeta(
				char c
				)
{
	return (c == '|' || c == '&' || c == '>' || c == '<' || c == '('
		|| c == ')');
}

static const char	*_expand_dollar(
						const char **start
						)
{
	static const char	*dollar = "$";
	static const char	*void_str = "";
	t_dyn_str			dyn_str;

	if (ft_ismeta(**start) || ft_isspace(**start) || **start == '\0')
		return (dollar);
	if (**start == '\'' || **start == '"')
		return (void_str);
	if (dyn_str_init(&dyn_str) != MS_OK)
		return (NULL);
	while (!ft_ismeta(**start) && !ft_isspace(**start) && **start != '\0'
		&& **start != '"' && **start != '\'' && **start != '$')
	{
		if (dyn_str_pushback(&dyn_str, **start) != MS_OK)
			return (NULL);
		++(*start);
	}
	dyn_str_destroy(&dyn_str);
	return (void_str);
}

static t_ms_error	_flush_word_read(
						t_lr_token_list *lrtoks,
						t_int_token *int_token
						)
{
	t_lr_token	lrtok;
	int			r;

	if (_token_gen_word(&lrtok, int_token->word_read.str))
		return (MS_FATAL);
	r = lrtoks_pushback(lrtoks, &lrtok);
	if (r != MS_OK)
		return (r);
	int_token->word_read.str = NULL;
	return (MS_OK);
}

// ************************************************************************** //
// *                                                                        * //
// * State functions implementation.                                        * //
// *                                                                        * //
// ************************************************************************** //

static t_ms_error	_state_dollar(
						t_lr_token_list *lrtoks,
						t_int_token *int_token
						)
{
	const char	*expended;
	int			r;

	expended = _expand_dollar(&int_token->cur);
	if (ft_isspace(*expended))
	{
		if (int_token->word_read.str != NULL)
		{
			r = _flush_word_read(lrtoks, int_token);
			if (r != MS_OK)
				return (r);
		}
	}
	while (*expended != '\0')
	{
		while (ft_isspace(*expended))
			++expended;
		while (!ft_isspace(*expended) && *expended != '\0')
			if (dyn_str_pushback(&int_token->word_read, *(expended++)))
				return (1);
		if (ft_isspace(*expended))
			if (_flush_word_read(lrtoks, int_token))
				return (1);
	}
	return (0);
}

static t_ms_error	_state_dollar_quoted(
						t_lr_token_list *lrtoks,
						t_int_token *int_token
						)
{
	const char	*expended;

	(void)(lrtoks);
	expended = _expand_dollar(&int_token->cur);
	if (expended == NULL)
		return (MS_FATAL);
	if (*expended != '\0')
	{
		if (int_token->word_read.str != NULL)
			return (dyn_str_cat(&int_token->word_read, expended));
		else
			return (dyn_str_cat(&int_token->word_read, expended));
	}
	return (MS_OK);
}

static t_ms_error	_state_initial(
						t_lr_token_list *lrtoks,
						t_int_token *int_token
						)
{
	const char	current = *int_token->cur;
	t_lr_token	lrtok;

	if (current == '\0')
		return (_token_gen_end(&lrtok) || lrtoks_pushback(lrtoks, &lrtok));
	++int_token->cur;
	if (current == '|')
		return (_state_pipe_or(lrtoks, int_token));
	if (current == '&')
		return (_state_and(lrtoks, int_token));
	if (current == '<')
		return (_state_in(lrtoks, int_token));
	if (current == '>')
		return (_state_out(lrtoks, int_token));
	if (current == '(')
		return (_token_gen_obracket(&lrtok) || lrtoks_pushback(lrtoks, &lrtok));
	if (current == ')')
		return (_token_gen_cbracket(&lrtok) || lrtoks_pushback(lrtoks, &lrtok));
	if (current == '*' && (ft_ismeta(*int_token->cur)
			|| ft_isspace(*int_token->cur) || *int_token->cur == '\0'))
		return (_token_gen_end(&lrtok) || lrtoks_pushback(lrtoks, &lrtok));
	if (current == '$')
		if (_state_dollar(lrtoks, int_token))
			return (1);
	if (current == '"')
		return (_state_doublequote(lrtoks, int_token));
	if (current == '\'')
		return (_state_quote(lrtoks, int_token));
	return ((current != '$' && dyn_str_pushback(&int_token->word_read, current))
		|| _state_word(lrtoks, int_token));
}

static t_ms_error	_state_out(
						t_lr_token_list *lrtoks,
						t_int_token *int_token
						)
{
	const char	current = *int_token->cur;
	t_lr_token	lrtok;

	if (current == '>')
	{
		++int_token->cur;
		if (_token_gen_io(&lrtok, IO_APPEND))
			return (MS_FATAL);
		return (lrtoks_pushback(lrtoks, &lrtok));
	}
	if (_token_gen_io(&lrtok, IO_OUT))
		return (MS_FATAL);
	return (lrtoks_pushback(lrtoks, &lrtok));
}

static t_ms_error	_state_in(
						t_lr_token_list *lrtoks,
						t_int_token *int_token
						)
{
	const char	current = *int_token->cur;
	t_lr_token	lrtok;

	if (current == '<')
	{
		++int_token->cur;
		if (_token_gen_io(&lrtok, IO_HEREDOC))
			return (MS_FATAL);
		return (lrtoks_pushback(lrtoks, &lrtok));
	}
	if (_token_gen_io(&lrtok, IO_IN))
		return (MS_FATAL);
	return (lrtoks_pushback(lrtoks, &lrtok));
}

static t_ms_error	_state_pipe_or(
						t_lr_token_list *lrtoks,
						t_int_token *int_token
						)
{
	const char	current = *int_token->cur;
	t_lr_token	lrtok;

	if (current == '|')
	{
		++int_token->cur;
		if (_token_gen_and_or(&lrtok, LOGIC_OR))
			return (MS_FATAL);
		return (lrtoks_pushback(lrtoks, &lrtok));
	}
	if (_token_gen_pipe(&lrtok))
		return (MS_FATAL);
	return (lrtoks_pushback(lrtoks, &lrtok));
}

static t_ms_error	_state_and(
						t_lr_token_list *lrtoks,
						t_int_token *int_token
						)
{
	const char	current = *int_token->cur;
	t_lr_token	lrtok;

	if (current != '&')
		return (MS_SYNTAX_ERROR);
	++int_token->cur;
	if (_token_gen_and_or(&lrtok, LOGIC_AND))
		return (MS_FATAL);
	return (lrtoks_pushback(lrtoks, &lrtok));
}

static t_ms_error	_state_word(
						t_lr_token_list *lrtoks,
						t_int_token *int_token
						)
{
	char		current;
	t_lr_token	lrtok;
	t_ms_error	r;

	current = *int_token->cur;
	while (current != '\0' && !ft_ismeta(current) && !ft_isspace(current))
	{
		++int_token->cur;
		if (current == '"')
			return (_state_doublequote(lrtoks, int_token));
		if (current == '\'')
			return (_state_quote(lrtoks, int_token));
		if (current == '$')
		{
			r = _state_dollar(lrtoks, int_token);
			if (r != MS_OK)
				return (r);
		}
		else
		{
			r = dyn_str_pushback(&int_token->word_read, current);
			if (r != MS_OK)
				return (r);
		}
		current = *int_token->cur;
	}
	if (int_token->word_read.str != NULL)
	{
		if (_token_gen_word(&lrtok, int_token->word_read.str))
			return (MS_FATAL);
		return (lrtoks_pushback(lrtoks, &lrtok));
	}
	return (MS_OK);
}

static t_ms_error	_init_dyn_str_if_null(
						t_int_token *int_token
						)
{
	int		r;

	if (int_token->word_read.str == NULL)
	{
		r = dyn_str_init(&int_token->word_read);
		if (r != MS_OK)
			return (r);
	}
	return (MS_OK);
}

static t_ms_error	_state_quote(
						t_lr_token_list *lrtoks,
						t_int_token *int_token
						)
{
	char	current;
	int		r;

	current = *int_token->cur;
	r = _init_dyn_str_if_null(int_token);
	if (r != MS_OK)
		return (r);
	while (current != '\'')
	{
		++int_token->cur;
		if (current == '\0')
			return (MS_SYNTAX_ERROR);
		r = dyn_str_pushback(&int_token->word_read, current);
		if (r != MS_OK)
			return (r);
		current = *int_token->cur;
	}
	++int_token->cur;
	return (_state_word(lrtoks, int_token));
}

static t_ms_error	_state_doublequote(
						t_lr_token_list *lrtoks,
						t_int_token *int_token
						)
{
	char	current;
	int		r;

	current = *int_token->cur;
	r = _init_dyn_str_if_null(int_token);
	if (r != MS_OK)
		return (r);
	while (current != '\"')
	{
		++int_token->cur;
		if (current == '\0')
			return (MS_SYNTAX_ERROR);
		if (current == '$')
		{
			r = _state_dollar_quoted(lrtoks, int_token);
			if (r != MS_OK)
				return (r);
		}
		else
		{
			r = dyn_str_pushback(&int_token->word_read, current);
			if (r != MS_OK)
				return (r);
		}
		current = *int_token->cur;
	}
	++int_token->cur;
	return (_state_word(lrtoks, int_token));
}
