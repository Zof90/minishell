/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azaytsev <azaytsev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/12 10:05:59 by azaytsev          #+#    #+#             */
/*   Updated: 2026/05/04 16:00:00 by azaytsev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gc.h"
#include "minishell.h"

t_cmd	*cmd_new(t_shell *shell)
{
	t_cmd	*cmd;

	cmd = gc_malloc(shell, sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->args = NULL;
	cmd->redirs = NULL;
	cmd->next = NULL;
	return (cmd);
}

void	cmd_add_back(t_cmd **list, t_cmd *new_cmd)
{
	t_cmd	*last;

	if (!new_cmd)
		return ;
	if (!*list)
	{
		*list = new_cmd;
		return ;
	}
	last = *list;
	while (last->next)
		last = last->next;
	last->next = new_cmd;
}

int	is_redir_type(t_token_type type)
{
	return (type == TOK_REDIR_IN || type == TOK_REDIR_OUT
		|| type == TOK_HEREDOC || type == TOK_APPEND);
}

int	count_cmd_args(t_token *tokens)
{
	int	count;
	int	skip;

	count = 0;
	skip = 0;
	while (tokens && tokens->type != TOK_PIPE)
	{
		if (skip)
			skip = 0;
		else if (is_redir_type(tokens->type))
			skip = 1;
		else if (tokens->type == TOK_WORD)
			count++;
		tokens = tokens->next;
	}
	return (count);
}
