/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zof <zof@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/09 15:33:25 by zof               #+#    #+#             */
/*   Updated: 2026/05/14 19:22:06 by zof              ###   ########.fr       */
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

static int	run_child(t_shell *shell, t_cmd *cmd, t_cmd *header,
		t_pipe *pipe_ctx)
{
	int		fd;
	t_cmd	*current;
	char	*path;

	fd = -1;
	current = cmd;
	while (current)
	{
		if (!is_builtin(current))
		{
			path = is_valide_cmd(shell, current);
			if (path)
				current->args[0] = path;
			else
			{
				if (ft_strchr(cmd->args[0], '/'))
					print_error(cmd->args[0], strerror(errno));
				else
					print_error(cmd->args[0], "command not found");
				if ((errno == EACCES))
					exit(126);
				exit(127);
			}
			if (!current->args[0])
			{
				shell->exit_status = 127;
				// return (false);
			}
		}
		current = current->next;
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
	print_error(cmd->args[0], strerror(errno));
	if ((errno == EACCES))
		exit(126);
	exit(127);
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

	// t_cmd	*current;
	// current = cmd;
	// while (current)
	// {
	// 	if (!is_builtin(current))
	// 	{
	// 		current->args[0] = is_valide_cmd(shell, current);
	// 		if (!current->args[0])
	// 		{
	// 			shell->exit_status = 127;
	// 			// return (false);
	// 		}
	// 	}
	// 	current = current->next;
	// }
	run_executor_util(shell, cmd, &pipe_ctx);
	wait_all(shell, cmd);
	return (true);
}

// size_t	count_pipe(t_cmd *cmd)
// {
// 	size_t	nb_pipe;

// 	nb_pipe = 0;
// 	while(cmd)
// 	{
// 		if (cmd->redirs)
// 		{
// 			if (cmd->redirs->type == TOK_PIPE)
// 				nb_pipe++;
// 		}
// 		cmd = cmd->next;
// 	}
// 	return(nb_pipe);
// }

// char	*is_redir(t_cmd *cmd)
// {
// 	int	i;

// 	i = 0;
// 	while(cmd->args[i])
// 	{
// 		if (cmd->args[i] == '<' || cmd->args[i] == '>' | cmd->args[i] == '>>')
// 			return(cmd->args[i]);
// 		i++;
// 	}
// 	return(NULL);
// }