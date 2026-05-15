/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zof <zof@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/09 15:33:25 by zof               #+#    #+#             */
/*   Updated: 2026/05/15 13:20:03 by zof              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gc.h"
#include "minishell.h"

static void	setup_child_pipe(t_cmd *cmd, t_cmd *header, t_pipe *pipe_ctx)
{
	if (cmd != header)
		dup2(pipe_ctx->prev_pipe, 0);
	if (cmd->next)
		dup2(pipe_ctx->pfd[1], 1);
	if (pipe_ctx->prev_pipe != -1)
		close(pipe_ctx->prev_pipe);
	if (cmd->next)
	{
		close(pipe_ctx->pfd[0]);
		close(pipe_ctx->pfd[1]);
	}
}

static void	run_child(t_shell *shell, t_cmd *cmd, t_cmd *header,
		t_pipe *pipe_ctx)
{
	int		fd;
	char	*path;

	fd = -1;
	if (!is_builtin(cmd))
	{
		path = is_valide_cmd(shell, cmd);
		if (!path)
			child_exit_error(cmd->args[0]);
		cmd->args[0] = path;
	}
	setup_child_pipe(cmd, header, pipe_ctx);
	while (cmd->redirs)
	{
		fd = run_redir(cmd->redirs, fd);
		if (fd == -1)
			exit(1);
		cmd->redirs = cmd->redirs->next;
	}
	if (is_builtin(cmd))
		run_builtin(shell, cmd, header);
	execve(cmd->args[0], cmd->args, 0);
	child_exit_error(cmd->args[0]);
}
static int	run_parent(t_cmd *cmd, t_pipe *pipe_ctx)
{
	if (pipe_ctx->prev_pipe != -1)
		close(pipe_ctx->prev_pipe);
	if (cmd->next)
	{
		close(pipe_ctx->pfd[1]);
		return (pipe_ctx->pfd[0]);
	}
	return (-1);
}
static void	run_executor_util(t_shell *shell, t_cmd *cmd, t_pipe *pipe_ctx)
{
	t_cmd	*current;

	current = cmd;
	pipe_ctx->prev_pipe = -1;
	while (current)
	{
		if (current->next)
			pipe(pipe_ctx->pfd);
		current->pid = fork();
		if (!current->pid)
		{
			signal(SIGINT, SIG_DFL);
			signal(SIGQUIT, SIG_DFL);
			run_child(shell, current, cmd, pipe_ctx);
		}
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
		pipe_ctx->prev_pipe = run_parent(cmd, pipe_ctx);
		current = current->next;
	}
}

bool	run_executor(t_shell *shell, t_cmd *cmd)
{
	t_pipe	pipe_ctx;

	run_executor_util(shell, cmd, &pipe_ctx);
	wait_all(shell, cmd);
	return (true);
}
