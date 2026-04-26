/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zof <zof@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/26 13:45:52 by zof               #+#    #+#             */
/*   Updated: 2026/04/26 17:48:38 by zof              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gc.h"
#include "minishell.h"

t_token_type set_type(t_token *new_node)
{
	if (new_node->value[0] == '<')
	{
		if (new_node->value[1] == '<')
			return(TOK_HEREDOC);
		return(TOK_REDIR_IN);
	}
	else if (*new_node->value == '>')
	{
		if (new_node->value[1] == '>')
			return(TOK_APPEND);
		return(TOK_REDIR_OUT);
	}
	else if (*new_node->value == '|')
		return(TOK_PIPE);
	else
		return(TOK_WORD);
}

static void	skip_spaces(char *line, int *i)
{
	while ((line[*i] == ' ') || (line[*i] >= 9 && line[*i] <= 13))
		*i++;
}
bool	is_opperator(char c)
{
	if (!(c != '>' && c != '<' && c != '|'))
		return (true);
	return (false);
}
t_token	*lex(t_shell *shell, char *line)
{
	int		i;
	bool	flag;
	t_token	*token;

	token = NULL;
	i = 0;
	while (line[i])
	{
		skip_spaces(&line[i], &i);
		if (is_opperator)
		{
			flag = lex_opperator(shell, &token, &line[i], &i);
			if (!flag)
				return (NULL);
		}
		else
		{
			flag = lex_word(shell, &token, &line[i], &i);
			if (!flag)
				return (NULL);
		}
	}
	return (token);
}
