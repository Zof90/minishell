/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azaytsev <azaytsev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/12 10:05:40 by azaytsev          #+#    #+#             */
/*   Updated: 2026/05/04 16:46:43 by azaytsev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gc.h"
#include "minishell.h"

static char	**alloc_args(t_shell *shell, t_token *tokens)
{
	int		count;
	char	**args;

	count = count_cmd_args(tokens);
	args = gc_malloc(shell, sizeof(char *) * (count + 1));
	if (!args)
		return (NULL);
	args[count] = NULL;
	return (args);
}

static int	fill_cmd(t_shell *shell, t_cmd *cmd, t_token **cur)
{
	int	i;

	cmd->args = alloc_args(shell, *cur);
	if (!cmd->args)
		return (1);
	i = 0;
	while (*cur && (*cur)->type != TOK_PIPE)
	{
		if (is_redir_type((*cur)->type))
		{
			if (parse_redir(shell, cur, &cmd->redirs))
				return (1);
		}
		else
		{
			cmd->args[i] = gc_strdup(shell, (*cur)->value);
			if (!cmd->args[i])
				return (1);
			i++;
			*cur = (*cur)->next;
		}
	}
	return (0);
}

t_cmd	*parse(t_shell *shell, t_token *tokens)
{
	t_cmd	*cmds;
	t_cmd	*cmd;

	cmds = NULL;
	while (tokens)
	{
		cmd = cmd_new(shell);
		if (!cmd || fill_cmd(shell, cmd, &tokens))
			return (NULL);
		cmd_add_back(&cmds, cmd);
		if (tokens && tokens->type == TOK_PIPE)
			tokens = tokens->next;
	}
	return (cmds);
}
