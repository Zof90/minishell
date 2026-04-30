/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_opperator.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zof <zof@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/26 13:59:14 by zof               #+#    #+#             */
/*   Updated: 2026/04/30 13:25:30 by zof              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gc.h"
#include "minishell.h"

static int	read_opperator(char *line)
{
	if (line[0] == '>' && line[1] == '>')
		return (2);
	else if (line[0] == '<' && line[1] == '<')
		return (2);
	return (1);
}

bool	lex_opperator(t_shell *shell, t_token **token, char *line, int *i)
{
	t_token	*new_node;
	int		len;

	new_node = gc_malloc(shell, sizeof(t_token));
	if (!new_node)
		return (false);
	len = read_opperator(line);
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
