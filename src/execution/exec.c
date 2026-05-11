/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zof <zof@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/09 15:33:25 by zof               #+#    #+#             */
/*   Updated: 2026/05/11 19:06:34 by zof              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gc.h"
#include "minishell.h"

char	*is_valid_cmd(t_shell *shell, t_cmd *cmd)
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
static bool	run_redir(t_redir *redirs, int fd, int *pfd)
{
	if (redirs->type == TOK_REDIR_IN)
	{
		fd = open(redirs->file, O_RDONLY);
		if (fd == -1)
			return (print_error(redirs->file, strerror(errno)), false);
		dup2(pfd[0], 0);
		close(fd);
	}
	else if (redirs->type == TOK_REDIR_OUT)
	{
		fd = open(redirs->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd == -1)
			return (print_error(redirs->file, strerror(errno)), false);
		dup2(pfd[1], 1);
		close(fd);
	}
	else if (redirs->type == TOK_APPEND)
	{
		fd = open(redirs->file, O_WRONLY | O_APPEND | O_TRUNC, 0644);
		if (fd == -1)
			return (print_error(redirs->file, strerror(errno)), false);
		dup2(pfd[1], 1);
		close(fd);
	}
	return (true);
}
//
static int	run_child(t_cmd *cmd, t_cmd *header, int prev_pipe, int *pfd)
{
	int	fd;

	fd = -1;
	if (cmd != header && cmd->next)
		dup2(prev_pipe, 0);
	if (cmd->next)
		dup2(pfd[1], 1);
	if (prev_pipe != -1)
		close(prev_pipe);
	if (cmd->next)
	{
		close(pfd[0]);
		close(pfd[1]);
	}
	if (cmd->redirs)
		run_redir(cmd->redirs, fd, pfd);
	execve(cmd->args[0], cmd->args, 0);
	print_error(cmd->args[0], strerror(errno));
	if ((errno == EACCES))
		exit(126);
	exit(127);
}
static int	run_parent(t_cmd *cmd, int prev_pipe, int *pfd)
{
	if (prev_pipe != -1)
		close(prev_pipe);
	if (cmd->next)
	{
		close(pfd[1]);
		return (pfd[0]);
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
			shell->exit_status = WTERMSIG(status);
		cmd = cmd->next;
	}
}
void	run_executor_util(t_cmd *cmd, int prev_pipe, int *pfd)
{
	t_cmd	*current;

	current = cmd;
	while (current)
	{
		if (!current->next)
		{
			execve(current->args[0], current->args, 0);
			print_error(current->args[0], strerror(errno));
			if ((errno == EACCES))
				exit(126);
			exit(127);
		}
		else
		{
			while (current)
			{
				if (current->next)
					pipe(pfd);
				current->pid = fork();
				if (!current->pid)
					run_child(current, cmd, prev_pipe, pfd);
				prev_pipe = run_parent(cmd, prev_pipe, pfd);
				current = current->next;
			}
		}
	}
}

bool	run_executor(t_shell *shell, t_cmd *cmd)
{
	int	pfd[2];
	int	prev_pipe;

	prev_pipe = -1;
	cmd->args[0] = is_valid_cmd(shell, cmd);
	if (!cmd->args[0])
		return (false);
	run_executor_util(cmd, prev_pipe, pfd);
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