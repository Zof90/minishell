/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_collect.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azaytsev <azaytsev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 09:00:00 by azaytsev          #+#    #+#             */
/*   Updated: 2026/05/15 09:00:00 by azaytsev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gc.h"
#include "minishell.h"

static int	hd_done(t_shell *shell, t_redir *redir, t_hd_ctx *ctx)
{
	redir->heredoc_content = hd_finalize(shell, ctx);
	if (!redir->heredoc_content)
		return (1);
	return (0);
}

static int	read_one_heredoc(t_shell *shell, t_redir *redir)
{
	char		*line;
	t_hd_ctx	ctx;

	ctx.head = NULL;
	ctx.tail = NULL;
	ctx.total = 0;
	while (1)
	{
		line = readline("> ");
		if (g_signal == SIGINT)
			return (free(line), 1);
		if (!line)
			return (warn_heredoc_eof(redir->file),
				hd_done(shell, redir, &ctx));
		if (ft_strcmp(line, redir->file) == 0)
			return (free(line), hd_done(shell, redir, &ctx));
		if (push_heredoc_line(shell, redir, line, &ctx))
			return (free(line), 1);
		free(line);
	}
}

static int	collect_loop(t_cmd *cmds, t_shell *shell)
{
	t_cmd	*cmd;
	t_redir	*redir;

	cmd = cmds;
	while (cmd)
	{
		redir = cmd->redirs;
		while (redir)
		{
			if (redir->type == TOK_HEREDOC
				&& read_one_heredoc(shell, redir))
				return (1);
			redir = redir->next;
		}
		cmd = cmd->next;
	}
	return (0);
}

int	collect_heredocs(t_cmd *cmds, t_shell *shell)
{
	int	saved_stdin;
	int	ret;

	saved_stdin = dup(STDIN_FILENO);
	if (saved_stdin == -1)
		return (1);
	g_signal = 0;
	setup_signals_heredoc();
	ret = collect_loop(cmds, shell);
	dup2(saved_stdin, STDIN_FILENO);
	close(saved_stdin);
	setup_signals_interactive();
	if (g_signal == SIGINT)
		return (g_signal = 0, 1);
	return (ret);
}
