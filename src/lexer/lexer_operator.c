/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_operator.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schouite <schouite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/26 13:59:14 by schouite          #+#    #+#             */
/*   Updated: 2026/05/01 13:51:57 by schouite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gc.h"
#include "minishell.h"

static int	read_operator(char *line)
{
	int	n;

	n = 0;
	while (line[n] >= '0' && line[n] <= '9')
		n++;
	if (line[n] == '>' && line[n + 1] == '>')
		return (n + 2);
	if (line[n] == '<' && line[n + 1] == '<')
		return (n + 2);
	return (n + 1);
}

bool	is_fd_redir(char *s)
{
	int	i;

	i = 0;
	while (s[i] >= '0' && s[i] <= '9')
		i++;
	if (i == 0)
		return (false);
	return (s[i] == '<' || s[i] == '>');
}

bool	lex_operator(t_shell *shell, t_token **token, char *line, int *i)
{
	t_token	*new_node;
	int		len;

	new_node = gc_malloc(shell, sizeof(t_token));
	if (!new_node)
		return (false);
	len = read_operator(line);
	new_node->value = gc_substr(shell, line, 0, len);
	if (!new_node->value)
		return (false);
	new_node->type = set_type(new_node);
	new_node->next = NULL;
	lstadd_back_token(token, new_node);
	*i += len;
	return (true);
}
