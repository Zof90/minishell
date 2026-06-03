/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azaytsev <azaytsev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/13 09:06:38 by azaytsev          #+#    #+#             */
/*   Updated: 2026/05/13 09:11:45 by azaytsev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gc.h"
#include "minishell.h"

static int	is_ambiguous_redir(char *old_file, char *new_file)
{
	if (field_has_quotes(old_file))
		return (0);
	if (field_count_words(new_file) != 1)
		return (1);
	return (0);
}

static int	expand_redir_file(t_redir *redir, t_shell *shell)
{
	char	*old_file;
	char	*new_file;

	old_file = redir->file;
	new_file = expand_str(old_file, shell);
	if (!new_file)
		return (1);
	if (is_ambiguous_redir(old_file, new_file))
	{
		print_error(old_file, "ambiguous redirect");
		shell->exit_status = 1;
		return (1);
	}
	restore_whitespace(new_file);
	redir->file = new_file;
	return (0);
}

static int	expand_redirs(t_redir *redir, t_shell *shell)
{
	while (redir)
	{
		if (redir->type != TOK_HEREDOC)
		{
			if (expand_redir_file(redir, shell))
				return (1);
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
