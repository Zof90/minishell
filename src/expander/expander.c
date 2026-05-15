/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azaytsev <azaytsev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/13 09:00:00 by azaytsev          #+#    #+#             */
/*   Updated: 2026/05/13 09:00:00 by azaytsev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gc.h"
#include "minishell.h"

static char	*expand_and_strip(const char *str, t_shell *shell)
{
	char	*expanded;

	expanded = expand_str(str, shell);
	if (!expanded)
		return (NULL);
	return (strip_quotes(shell, expanded));
}

static int	expand_args(t_cmd *cmd, t_shell *shell)
{
	int		i;
	char	*new_val;

	i = 0;
	while (cmd->args && cmd->args[i])
	{
		new_val = expand_and_strip(cmd->args[i], shell);
		if (!new_val)
			return (1);
		cmd->args[i] = new_val;
		i++;
	}
	return (0);
}

static int	expand_redirs(t_redir *redir, t_shell *shell)
{
	char	*new_file;

	while (redir)
	{
		if (redir->type != TOK_HEREDOC)
		{
			new_file = expand_and_strip(redir->file, shell);
			if (!new_file)
				return (1);
			redir->file = new_file;
		}
		redir = redir->next;
	}
	return (0);
}

t_cmd	*expand(t_cmd *cmds, t_shell *shell)
{
	t_cmd	*cur;

	cur = cmds;
	while (cur)
	{
		if (expand_args(cur, shell) || expand_redirs(cur->redirs, shell))
			return (NULL);
		cur = cur->next;
	}
	return (cmds);
}
