/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_word.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schouite <schouite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/26 14:38:42 by schouite          #+#    #+#             */
/*   Updated: 2026/05/01 14:40:07 by schouite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gc.h"
#include "minishell.h"

static t_quote_state	handle_quotes(t_quote_state state, char c)
{
	if (state == DEFAULT)
	{
		if (c == '\'')
			return (IN_SQUOTE);
		else if (c == '\"')
			return (IN_DQUOTE);
	}
	else if (state == IN_SQUOTE)
	{
		if (c == '\'')
			state = DEFAULT;
	}
	else if (state == IN_DQUOTE)
	{
		if (c == '\"')
			return (DEFAULT);
	}
	return (state);
}

static bool	is_spaces(char c)
{
	if ((c == ' ') || (c >= 9 && c <= 13))
		return (true);
	return (false);
}

static int	read_word(char *line)
{
	t_quote_state	state;
	int				len;

	len = 0;
	state = DEFAULT;
	while (line[len])
	{
		if ((is_operator(line[len]) || is_spaces(line[len]))
			&& state == DEFAULT)
			break ;
		state = handle_quotes(state, line[len]);
		len++;
	}
	if (state != DEFAULT)
		return (-1);
	return (len);
}

bool	lex_word(t_shell *shell, t_token **token, char *line, int *i)
{
	t_token	*new_node;
	int		len;

	len = read_word(line);
	if (len < 0)
	{
		print_error(NULL, "unclosed quote");
		return (false);
	}
	if (!len)
		return (true);
	new_node = gc_malloc(shell, sizeof(t_token));
	if (!new_node)
		return (false);
	new_node->value = gc_substr(shell, line, 0, len);
	if (!new_node->value)
		return (false);
	new_node->type = set_type(new_node);
	new_node->next = NULL;
	lstadd_back_token(token, new_node);
	*i += len;
	return (true);
}
