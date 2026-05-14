/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_util.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zof <zof@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/14 16:35:29 by zof               #+#    #+#             */
/*   Updated: 2026/05/14 17:24:01 by zof              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
bool	is_builtin(t_cmd *cmd)
{
	if (ft_strcmp(cmd->args[0], "echo") == 0)
		return (true);
	if (ft_strcmp(cmd->args[0], "pwd") == 0)
		return (true);
	if (ft_strcmp(cmd->args[0], "cd") == 0)
		return (true);
	if (ft_strcmp(cmd->args[0], "export") == 0)
		return (true);
	if (ft_strcmp(cmd->args[0], "unset") == 0)
		return (true);
	if (ft_strcmp(cmd->args[0], "env") == 0)
		return (true);
	if (ft_strcmp(cmd->args[0], "exit") == 0)
		return (true);
	return (false);
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
	return (0);
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