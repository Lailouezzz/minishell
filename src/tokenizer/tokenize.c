/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-boud <ale-boud@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 15:22:16 by ale-boud          #+#    #+#             */
/*   Updated: 2023/12/11 12:41:00 by ale-boud         ###   ########.fr       */
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

// ************************************************************************** //
// *                                                                        * //
// * States function prototypes.                                            * //
// *                                                                        * //
// ************************************************************************** //

static int			_state_dollar(
						t_lr_token *lrtok,
						t_int_token *int_token
						);

static int			_state_initial(
						t_lr_token *lrtok,
						t_int_token *int_token
						);

static int			_state_out(
						t_lr_token *lrtok,
						t_int_token *int_token
						);

static int			_state_in(
						t_lr_token *lrtok,
						t_int_token *int_token
						);

static int			_state_pipe_or(
						t_lr_token *lrtok,
						t_int_token *int_token
						);

static int			_state_and(
						t_lr_token *lrtok,
						t_int_token *int_token
						);

static int			_state_word(
						t_lr_token *lrtok,
						t_int_token *int_token
						);

static int			_state_quote(
						t_lr_token *lrtok,
						t_int_token *int_token
						);

static int			_state_doublequote(
						t_lr_token *lrtok,
						t_int_token *int_token
						);

// ************************************************************************** //
// *                                                                        * //
// * Header functions.                                                      * //
// *                                                                        * //
// ************************************************************************** //

int	tokenize(
		t_lr_token *lrtok,
		const char **start
		)
{
	t_int_token	int_token;
	int			r;

	int_token.cur = *start;
	while (ft_isspace(*int_token.cur) && *int_token.cur != '\0')
		++int_token.cur;
	r = _state_initial(lrtok, &int_token);
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

// ************************************************************************** //
// *                                                                        * //
// * State functions implementation.                                        * //
// *                                                                        * //
// ************************************************************************** //

static const char	*_expand_dollar(
				const char **start
				)
{
	static const char	*dollar = "$";
	static const char	*truc = "EXPANDED VALUE";
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
	return (truc);
}

static int	_state_dollar(
				t_lr_token *lrtok,
				t_int_token *int_token
				)
{
	const char	*expended;

	(void)(lrtok);
	expended = _expand_dollar(&int_token->cur);
	if (expended == NULL)
		return (1);
	if (*expended != '\0')
	{
		if (int_token->word_read.str != NULL)
			return (dyn_str_cat(&int_token->word_read, expended));
		else
			return (dyn_str_init(&int_token->word_read)
				|| dyn_str_cat(&int_token->word_read, expended));
	}
	return (0);
}

static int	_state_initial(
				t_lr_token *lrtok,
				t_int_token *int_token
				)
{
	const char	current = *int_token->cur;

	if (current == '\0')
		return (_token_gen_end(lrtok));
	++int_token->cur;
	if (current == '|')
		return (_state_pipe_or(lrtok, int_token));
	if (current == '&')
		return (_state_and(lrtok, int_token));
	if (current == '<')
		return (_state_in(lrtok, int_token));
	if (current == '>')
		return (_state_out(lrtok, int_token));
	if (current == '(')
		return (_token_gen_obracket(lrtok));
	if (current == ')')
		return (_token_gen_cbracket(lrtok));
	if (current == '*' && (ft_ismeta(*int_token->cur)
			|| ft_isspace(*int_token->cur) || *int_token->cur == '\0'))
		return (_token_gen_wildcard(lrtok));
	if (dyn_str_init(&int_token->word_read))
		return (1);
	if (current == '"')
		return (_state_doublequote(lrtok, int_token));
	if (current == '\'')
		return (_state_quote(lrtok, int_token));
	if (current == '$' && _state_dollar(lrtok, int_token))
		return (1);
	return ((current != '$' && dyn_str_pushback(&int_token->word_read, current))
		|| _state_word(lrtok, int_token));
}

static int	_state_out(
				t_lr_token *lrtok,
				t_int_token *int_token
				)
{
	const char	current = *int_token->cur;

	if (current == '>')
	{
		++int_token->cur;
		return (_token_gen_io(lrtok, IO_APPEND));
	}
	return (_token_gen_io(lrtok, IO_OUT));
}

static int	_state_in(
				t_lr_token *lrtok,
				t_int_token *int_token
				)
{
	const char	current = *int_token->cur;

	if (current == '<')
	{
		++int_token->cur;
		return (_token_gen_io(lrtok, IO_HEREDOC));
	}
	return (_token_gen_io(lrtok, IO_IN));
}

static int	_state_pipe_or(
				t_lr_token *lrtok,
				t_int_token *int_token
				)
{
	const char	current = *int_token->cur;

	if (current == '|')
	{
		++int_token->cur;
		return (_token_gen_and_or(lrtok, LOGIC_OR));
	}
	return (_token_gen_pipe(lrtok));
}

static int	_state_and(
				t_lr_token *lrtok,
				t_int_token *int_token
				)
{
	const char	current = *int_token->cur;

	if (current != '&')
		return (1);
	++int_token->cur;
	return (_token_gen_and_or(lrtok, LOGIC_AND));
}

static int	_state_word(
				t_lr_token *lrtok,
				t_int_token *int_token
				)
{
	char	current;

	current = *int_token->cur;
	while (current != '\0' && !ft_ismeta(current) && !ft_isspace(current))
	{
		++int_token->cur;
		if (current == '"')
			return (_state_doublequote(lrtok, int_token));
		if (current == '\'')
			return (_state_quote(lrtok, int_token));
		if (current == '$')
		{
			if (_state_dollar(lrtok, int_token))
			{
				dyn_str_destroy(&int_token->word_read);
				return (1);
			}
		}
		else if (dyn_str_pushback(&int_token->word_read, current))
			return (1);
		current = *int_token->cur;
	}
	return (_token_gen_word(lrtok, int_token->word_read.str));
}

static int	_state_quote(
				t_lr_token *lrtok,
				t_int_token *int_token
				)
{
	char	current;

	current = *int_token->cur;
	while (current != '\'')
	{
		++int_token->cur;
		if (current == '\0')
		{
			dyn_str_destroy(&int_token->word_read);
			return (1);
		}
		if (dyn_str_pushback(&int_token->word_read, current))
			return (1);
		current = *int_token->cur;
	}
	++int_token->cur;
	return (_state_word(lrtok, int_token));
}

static int	_state_doublequote(
				t_lr_token *lrtok,
				t_int_token *int_token
				)
{
	char	current;

	current = *int_token->cur;
	while (current != '\"')
	{
		++int_token->cur;
		if (current == '\0')
		{
			dyn_str_destroy(&int_token->word_read);
			return (1);
		}
		if (current == '$')
		{
			if (_state_dollar(lrtok, int_token))
			{
				dyn_str_destroy(&int_token->word_read);
				return (1);
			}
		}
		else if (dyn_str_pushback(&int_token->word_read, current))
			return (1);
		current = *int_token->cur;
	}
	++int_token->cur;
	return (_state_word(lrtok, int_token));
}
