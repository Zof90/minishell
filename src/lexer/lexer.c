/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zof <zof@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/26 13:45:52 by zof               #+#    #+#             */
/*   Updated: 2026/05/01 14:39:51 by zof              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gc.h"
#include "minishell.h"

static void	skip_spaces(char *line, int *i)
{
	while ((line[*i] == ' ') || (line[*i] >= 9 && line[*i] <= 13))
		*i += 1;
}

void	lstadd_back_token(t_token **lst, t_token *new)
{
	t_token	*tmp;

	if (!new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	tmp = *lst;
	while (tmp->next)
	{
		tmp = tmp->next;
	}
	tmp->next = new;
}

t_token_type	set_type(t_token *new_node)
{
	if (new_node->value[0] == '<')
	{
		if (new_node->value[1] == '<')
			return (TOK_HEREDOC);
		return (TOK_REDIR_IN);
	}
	else if (new_node->value[0] == '>')
	{
		if (new_node->value[1] == '>')
			return (TOK_APPEND);
		return (TOK_REDIR_OUT);
	}
	else if (new_node->value[0] == '|')
		return (TOK_PIPE);
	else
		return (TOK_WORD);
}

bool	is_opperator(char c)
{
	return (c == '>' || c == '<' || c == '|');
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
		skip_spaces(line, &i);
		if (!line[i])
			break ;
		if (is_opperator(line[i]))
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
