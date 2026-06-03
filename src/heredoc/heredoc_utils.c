/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azaytsev <azaytsev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 09:19:42 by azaytsev          #+#    #+#             */
/*   Updated: 2026/05/18 09:24:49 by azaytsev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gc.h"
#include "minishell.h"

void	warn_heredoc_eof(const char *delim)
{
	const char	*p[4];

	p[0] = "minishell: warning: here-document delimited by EOF (wanted `";
	p[1] = delim;
	p[2] = "')\n";
	p[3] = NULL;
	print_error_parts(p);
}

char	*hd_finalize(t_shell *shell, t_hd_ctx *ctx)
{
	char		*buf;
	t_hd_line	*node;
	size_t		pos;
	size_t		n;

	buf = gc_malloc(shell, ctx->total + 1);
	if (!buf)
		return (NULL);
	pos = 0;
	node = ctx->head;
	while (node)
	{
		n = ft_strlen(node->text);
		ft_memcpy(buf + pos, node->text, n);
		pos += n;
		buf[pos++] = '\n';
		node = node->next;
	}
	buf[pos] = '\0';
	return (buf);
}

int	push_heredoc_line(t_shell *shell, t_redir *redir, char *line, t_hd_ctx *ctx)
{
	char		*piece;
	t_hd_line	*node;

	if (redir->heredoc_quoted)
		piece = gc_strdup(shell, line);
	else
		piece = expand_heredoc(line, shell);
	if (!piece)
		return (1);
	node = gc_malloc(shell, sizeof(t_hd_line));
	if (!node)
		return (1);
	node->text = piece;
	node->next = NULL;
	if (!ctx->head)
		ctx->head = node;
	else
		ctx->tail->next = node;
	ctx->tail = node;
	ctx->total += ft_strlen(piece) + 1;
	return (0);
}

int	apply_heredoc(t_redir *redir)
{
	int	pfd[2];

	if (pipe(pfd) == -1)
	{
		print_error("heredoc", strerror(errno));
		return (-1);
	}
	if (spawn_heredoc_writer(redir, pfd) == -1)
	{
		close(pfd[0]);
		close(pfd[1]);
		return (-1);
	}
	close(pfd[1]);
	if (dup2(pfd[0], 0) == -1)
	{
		close(pfd[0]);
		print_error("heredoc", strerror(errno));
		return (-1);
	}
	close(pfd[0]);
	return (0);
}
