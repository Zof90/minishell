/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_opperator.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zof <zof@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/26 13:59:14 by zof               #+#    #+#             */
/*   Updated: 2026/04/27 16:06:15 by zof              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gc.h"
#include "minishell.h"

static int	read_opperator(char *line)
{
	char	*line_op;

	if (!line[1])
		return (1);
	line_op = malloc(3);
	if (!line_op)
		return (0);
	ft_strlcpy(line_op, line, 3);
	if (!ft_strcmp(line_op, ">>") || !ft_strcmp(line_op, "<<"))
		return (free(line_op), 2);
	else
		return (free(line_op), 1);
}

bool	lex_opperator(t_shell *shell, t_token **token, char *line, int *i)
{
	t_token	*new_node;
	int		len;

	new_node = gc_malloc(shell, sizeof(new_node));
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
