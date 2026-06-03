/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schouite <schouite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/09 15:33:25 by schouite          #+#    #+#             */
/*   Updated: 2026/05/16 15:12:21 by schouite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gc.h"
#include "minishell.h"

static void	setup_child_fd(t_cmd *cmd, t_cmd *header, t_pipe *pipe_ctx)
{
	if (cmd != header && dup2(pipe_ctx->prev_pipe, 0) == -1)
	{
		perror("minishell: dup2");
		exit(1);
	}
	if (cmd->next && dup2(pipe_ctx->pfd[1], 1) == -1)
	{
		perror("minishell: dup2");
		exit(1);
	}
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
	char	*path;
	char	**env;

	setup_child_fd(cmd, header, pipe_ctx);
	while (cmd->redirs)
	{
		if (run_redir(cmd->redirs, -1) == -1)
			exit(1);
		cmd->redirs = cmd->redirs->next;
	}
	if (!cmd->args || !cmd->args[0])
		exit(0);
	if (is_builtin(cmd))
		run_builtin(shell, cmd, header);
	path = is_valid_cmd(shell, cmd);
	if (!path)
		child_exit_error(shell, cmd->args[0]);
	env = env_to_array(shell->env);
	execve(path, cmd->args, env);
	child_exit_error(shell, cmd->args[0]);
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
		if (!setup_pipe(shell, current, pipe_ctx))
			return ;
		current->pid = fork();
		if (current->pid == -1)
		{
			perror("minishell: fork");
			shell->exit_status = 1;
			return ;
		}
		if (!current->pid)
		{
			setup_signals_child();
			run_child(shell, current, cmd, pipe_ctx);
		}
		setup_signals_exec();
		pipe_ctx->prev_pipe = run_parent(current, pipe_ctx);
		current = current->next;
	}
}

bool	run_executor(t_shell *shell, t_cmd *cmd)
{
	t_pipe	pipe_ctx;

	run_executor_util(shell, cmd, &pipe_ctx);
	wait_all(shell, cmd);
	setup_signals_interactive();
	return (true);
}
