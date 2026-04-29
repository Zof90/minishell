/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_word.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zof <zof@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/26 14:38:42 by zof               #+#    #+#             */
/*   Updated: 2026/04/27 18:12:08 by zof              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gc.h"
#include "minishell.h"

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
		if ((is_opperator(line[len]) || is_spaces(line[len]))
			&& state == DEFAULT)
		{
			break ;
		}
		if (state == DEFAULT)
		{
			if (line[len] == '\'')
				state = IN_SQUOTE;
			else if (line[len] == '\"')
				state = IN_DQUOTE;
			if (len)
			{
				state = DEFAULT;
				break;
			}
		}
		else if (state == IN_SQUOTE)
		{
			if (line[len] == '\'')
				state = DEFAULT;
		}
		else if (state == IN_DQUOTE)
		{
			if (line[len] == '\"')
				state = DEFAULT;
		}
		len += 1;
	}
	if (state != DEFAULT)
		return (0);
	return (len);
}

bool	lex_word(t_shell *shell, t_token **token, char *line, int *i)
{
	t_token	*new_node;
	int		len;

	new_node = gc_malloc(shell, sizeof(t_token));
	if (!new_node)
		return (false);
	len = read_word(line);
	if (!len)
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
