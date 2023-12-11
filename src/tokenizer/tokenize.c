/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-boud <ale-boud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 15:22:16 by ale-boud          #+#    #+#             */
/*   Updated: 2023/12/11 18:48:54 by ale-boud         ###   ########.fr       */
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

#include "utils.h"

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

static int			_flush_word_read(
						t_lr_token_list *lrtoks,
						t_int_token *int_token
						);

// ************************************************************************** //
// *                                                                        * //
// * States function prototypes.                                            * //
// *                                                                        * //
// ************************************************************************** //

static int			_state_dollar(
						t_lr_token_list *lrtoks,
						t_int_token *int_token
						);

static int			_state_dollar_quoted(
						t_lr_token_list *lrtoks,
						t_int_token *int_token
						);

static int			_state_initial(
						t_lr_token_list *lrtoks,
						t_int_token *int_token
						);

static int			_state_out(
						t_lr_token_list *lrtoks,
						t_int_token *int_token
						);

static int			_state_in(
						t_lr_token_list *lrtoks,
						t_int_token *int_token
						);

static int			_state_pipe_or(
						t_lr_token_list *lrtoks,
						t_int_token *int_token
						);

static int			_state_and(
						t_lr_token_list *lrtoks,
						t_int_token *int_token
						);

static int			_state_word(
						t_lr_token_list *lrtoks,
						t_int_token *int_token
						);

static int			_state_quote(
						t_lr_token_list *lrtoks,
						t_int_token *int_token
						);

static int			_state_doublequote(
						t_lr_token_list *lrtoks,
						t_int_token *int_token
						);

// ************************************************************************** //
// *                                                                        * //
// * Header functions.                                                      * //
// *                                                                        * //
// ************************************************************************** //

int	tokenize(
		t_lr_token_list *lrtoks,
		const char **start
		)
{
	t_int_token	int_token;
	int			r;

	if (lrtoks_init(lrtoks))
		return (1);
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
	if (dyn_str_init(&dyn_str))
		return (NULL);
	while (!ft_ismeta(**start) && !ft_isspace(**start) && **start != '\0'
		&& **start != '"' && **start != '\'' && **start != '$')
	{
		if (dyn_str_pushback(&dyn_str, **start))
			return (NULL);
		++(*start);
	}
	dyn_str_destroy(&dyn_str);
	return (void_str);
}

static int	_flush_word_read(
				t_lr_token_list *lrtoks,
				t_int_token *int_token
				)
{
	t_lr_token	lrtok;
	int			r;

	r = (_token_gen_word(&lrtok, int_token->word_read.str)
			|| lrtoks_pushback(lrtoks, &lrtok));
	int_token->word_read.str = NULL;
	return (r);
}

// ************************************************************************** //
// *                                                                        * //
// * State functions implementation.                                        * //
// *                                                                        * //
// ************************************************************************** //

static int	_state_dollar(
				t_lr_token_list *lrtoks,
				t_int_token *int_token
				)
{
	const char	*expended;

	expended = _expand_dollar(&int_token->cur);
	if (ft_isspace(*expended))
		if (int_token->word_read.str != NULL
			&& _flush_word_read(lrtoks, int_token))
			return (1);
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

static int	_state_dollar_quoted(
				t_lr_token_list *lrtoks,
				t_int_token *int_token
				)
{
	const char	*expended;

	(void)(lrtoks);
	expended = _expand_dollar(&int_token->cur);
	if (expended == NULL)
		return (1);
	if (*expended != '\0')
	{
		if (int_token->word_read.str != NULL)
			return (dyn_str_cat(&int_token->word_read, expended));
		else
			return (dyn_str_cat(&int_token->word_read, expended));
	}
	return (0);
}

static int	_state_initial(
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
		return (_token_gen_wildcard(&lrtok) || lrtoks_pushback(lrtoks, &lrtok));
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

static int	_state_out(
				t_lr_token_list *lrtoks,
				t_int_token *int_token
				)
{
	const char	current = *int_token->cur;
	t_lr_token	lrtok;

	if (current == '>')
	{
		++int_token->cur;
		return (_token_gen_io(&lrtok, IO_APPEND)
			|| lrtoks_pushback(lrtoks, &lrtok));
	}
	return (_token_gen_io(&lrtok, IO_OUT) || lrtoks_pushback(lrtoks, &lrtok));
}

static int	_state_in(
				t_lr_token_list *lrtoks,
				t_int_token *int_token
				)
{
	const char	current = *int_token->cur;
	t_lr_token	lrtok;

	if (current == '<')
	{
		++int_token->cur;
		return (_token_gen_io(&lrtok, IO_HEREDOC)
			|| lrtoks_pushback(lrtoks, &lrtok));
	}
	return (_token_gen_io(&lrtok, IO_IN) || lrtoks_pushback(lrtoks, &lrtok));
}

static int	_state_pipe_or(
				t_lr_token_list *lrtoks,
				t_int_token *int_token
				)
{
	const char	current = *int_token->cur;
	t_lr_token	lrtok;

	if (current == '|')
	{
		++int_token->cur;
		return (_token_gen_and_or(&lrtok, LOGIC_OR)
			|| lrtoks_pushback(lrtoks, &lrtok));
	}
	return (_token_gen_pipe(&lrtok) || lrtoks_pushback(lrtoks, &lrtok));
}

static int	_state_and(
				t_lr_token_list *lrtoks,
				t_int_token *int_token
				)
{
	const char	current = *int_token->cur;
	t_lr_token	lrtok;

	if (current != '&')
		return (1);
	++int_token->cur;
	return (_token_gen_and_or(&lrtok, LOGIC_AND)
		|| lrtoks_pushback(lrtoks, &lrtok));
}

static int	_state_word(
				t_lr_token_list *lrtoks,
				t_int_token *int_token
				)
{
	char		current;
	t_lr_token	lrtok;

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
			if (_state_dollar(lrtoks, int_token))
				return (1);
		}
		else if (dyn_str_pushback(&int_token->word_read, current))
			return (1);
		current = *int_token->cur;
	}
	return (int_token->word_read.str != NULL
		&& (_token_gen_word(&lrtok, int_token->word_read.str)
			|| lrtoks_pushback(lrtoks, &lrtok)));
}

static int	_state_quote(
				t_lr_token_list *lrtoks,
				t_int_token *int_token
				)
{
	char	current;

	current = *int_token->cur;
	if (int_token->word_read.str == NULL
		&& dyn_str_init(&int_token->word_read))
		return (1);
	while (current != '\'')
	{
		++int_token->cur;
		if (current == '\0')
			return (1);
		if (dyn_str_pushback(&int_token->word_read, current))
			return (1);
		current = *int_token->cur;
	}
	++int_token->cur;
	return (_state_word(lrtoks, int_token));
}

static int	_state_doublequote(
				t_lr_token_list *lrtoks,
				t_int_token *int_token
				)
{
	char	current;

	current = *int_token->cur;
	if (int_token->word_read.str == NULL
		&& dyn_str_init(&int_token->word_read))
		return (1);
	while (current != '\"')
	{
		++int_token->cur;
		if (current == '\0')
			return (1);
		if (current == '$' && _state_dollar_quoted(lrtoks, int_token))
			return (1);
		else if (dyn_str_pushback(&int_token->word_read, current))
			return (1);
		current = *int_token->cur;
	}
	++int_token->cur;
	return (_state_word(lrtoks, int_token));
}
