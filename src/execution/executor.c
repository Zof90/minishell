/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zof <zof@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/09 15:33:25 by zof               #+#    #+#             */
/*   Updated: 2026/05/13 19:44:41 by zof              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gc.h"
#include "minishell.h"

char	*is_valide_cmd(t_shell *shell, t_cmd *cmd)
{
	char	*str_pathname;
	char	**tmp_tab_pathname;

	if (cmd->args[0][0] == '/')
	{
		str_pathname = is_valide_pathname(cmd->args);
		return (str_pathname);
	}
	tmp_tab_pathname = make_pathname(shell, cmd);
	if (!tmp_tab_pathname)
		return (NULL);
	str_pathname = is_valide_pathname(tmp_tab_pathname);
	return (str_pathname);
}
int	run_redir(t_redir *redirs, int fd)
{
	if (redirs->type == TOK_REDIR_IN)
	{
		fd = open(redirs->file, O_RDONLY);
		if (fd == -1)
			return (print_error(redirs->file, strerror(errno)), -1);
		dup2(fd, 0);
		close(fd);
	}
	else if (redirs->type == TOK_REDIR_OUT)
	{
		fd = open(redirs->file, O_WRONLY | O_TRUNC | O_CREAT, 0644);
		if (fd == -1)
			return (print_error(redirs->file, strerror(errno)), -1);
		dup2(fd, 1);
		close(fd);
	}
	else if (redirs->type == TOK_APPEND)
	{
		fd = open(redirs->file, O_WRONLY | O_APPEND | O_CREAT, 0644);
		if (fd == -1)
			return (print_error(redirs->file, strerror(errno)), -1);
		dup2(fd, 1);
		close(fd);
	}
	return (1);
}
static int	run_child(t_shell *shell, t_cmd *cmd, t_cmd *header, t_pipe *pipe_ctx)
{
	int	fd;

	fd = -1;
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
	if (cmd->redirs)
	{
		fd = run_redir(cmd->redirs, fd);
		if (fd == -1)
			exit(1);
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
void	wait_all(t_shell *shell, t_cmd *cmd)
{
	int	status;

	status = 0;
	while (cmd)
	{
		waitpid(cmd->pid, &status, 0);
		if (WIFEXITED(status))
			shell->exit_status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
		{
			shell->exit_status = 128 + WTERMSIG(status);
			if (WTERMSIG(status) == SIGINT)
				printf("\n");
			else if (WTERMSIG(status) == SIGQUIT)
				printf("Quit (core dumped)\n");
		}
		cmd = cmd->next;
	}
}
void	run_executor_util(t_shell *shell, t_cmd *cmd, t_pipe *pipe_ctx)
{
	t_cmd	*current;

	current = cmd;
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
	t_pipe pipe_ctx;
	t_cmd	*current;

	current = cmd;
	while (current)
	{
		if (!is_builtin(current))
		{
			current->args[0] = is_valide_cmd(shell, current);
			if (!current->args[0])
				return (false);
		}
		current = current->next;
	}
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