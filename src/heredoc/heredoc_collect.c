/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_collect.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azaytsev <azaytsev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 09:30:12 by azaytsev          #+#    #+#             */
/*   Updated: 2026/05/15 09:35:19 by azaytsev         ###   ########.fr       */
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

static int	check_heredoc_done(t_shell *shell, t_redir *redir,
		t_hd_ctx *ctx, char *line)
{
	if (!line)
	{
		warn_heredoc_eof(redir->file);
		return (hd_done(shell, redir, ctx));
	}
	if (ft_strcmp(line, redir->file) == 0)
	{
		free(line);
		return (hd_done(shell, redir, ctx));
	}
	return (-1);
}

static int	read_one_heredoc(t_shell *shell, t_redir *redir)
{
	char		*line;
	t_hd_ctx	ctx;
	int			status;

	ctx.head = NULL;
	ctx.tail = NULL;
	ctx.total = 0;
	while (1)
	{
		line = read_hd_line();
		if (g_signal == SIGINT)
		{
			free(line);
			return (1);
		}
		status = check_heredoc_done(shell, redir, &ctx, line);
		if (status != -1)
			return (status);
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
	{
		g_signal = 0;
		return (1);
	}
	return (ret);
}
