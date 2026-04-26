/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_word.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zof <zof@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/26 14:38:42 by zof               #+#    #+#             */
/*   Updated: 2026/04/26 17:50:57 by zof              ###   ########.fr       */
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
static int	read_word(char *line, int *len)
{
	t_quote_state	state;

	state = DEFAULT;
	while (line[*len])
	{
		if (is_opperator(line[*len]) || is_spaces(line[*len]))
			break ;
		if (state == DEFAULT)
		{
			if (line[*len] == '\'')
				state = IN_SQUOTE;
			else if (line[*len] == '\"')
				state = IN_DQUOTE;
		}
		else if (state == IN_SQUOTE)
			if (line[*len] = '\'')
				state = DEFAULT;
			else if (state == IN_DQUOTE)
				if (line[*len] == '\"')
					state = DEFAULT;
		*len++;
	}
	if (state != DEFAULT)
		return (0);
	return (*len);
}

t_token	*lex_word(t_shell *shell, t_token **token, char *line, int *i)
{
	t_token	*new_node;
	int		len;

	new_node = gc_malloc(shell, sizeof(t_token));
	if (!new_node)
		return (NULL);
	len = 0;
	if (!read_word(line, &len))
		return (NULL);
	new_node->value = gc_substr(shell, line, 0, len);
	if (!new_node->value)
		return (NULL);
	new_node->next = NULL;
	new_node->type = set_type(new_node);
	lstadd_back_token(token, new_node);
	i += ++len;
	return (token);
}

// if (state == DEFAULT)
// {
//     if (line[pos] == '\'')
//         state = IN_SQUOTE;
//     else if (line[pos] == '\"')
//         state = IN_DQUOTE;
//     i++;
// }
// else if (state == IN_SQUOTE)
// {
// 	if (line[pos] = '\'')
// 	{
// 		state = DEFAULT;
// 		i++;
// 	}
// 	else
// 		i++;
// }
// else if (state == IN_DQUOTE)
// {
// 	if (line[pos] == '\"')
// 	{
// 		state = DEFAULT;
// 		i++;
// 	}
// 	else
// 		i++;
// }