/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azaytsev <azaytsev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 09:00:00 by azaytsev          #+#    #+#             */
/*   Updated: 2026/05/15 09:00:00 by azaytsev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gc.h"
#include "minishell.h"

void	warn_heredoc_eof(const char *delim)
{
	ft_putstr_fd("minishell: warning: here-document delimited by EOF (wanted `",
		2);
	ft_putstr_fd((char *)delim, 2);
	ft_putendl_fd("')", 2);
}

char	*append_heredoc_line(t_shell *shell, char *body, char *line)
{
	char	*with_nl;

	with_nl = gc_strjoin(shell, line, "\n");
	if (!with_nl)
		return (NULL);
	if (!body)
		return (with_nl);
	return (gc_strjoin(shell, body, with_nl));
}

int	push_heredoc_line(t_shell *shell, t_redir *redir, char *line, char **body)
{
	char	*piece;

	if (redir->heredoc_quoted)
		piece = gc_strdup(shell, line);
	else
		piece = expand_str(line, shell);
	if (!piece)
		return (1);
	*body = append_heredoc_line(shell, *body, piece);
	if (!*body)
		return (1);
	return (0);
}
