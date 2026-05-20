/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_util.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zof <zof@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/14 16:35:29 by zof               #+#    #+#             */
/*   Updated: 2026/05/16 15:10:54 by zof              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*is_valid_cmd(t_shell *shell, t_cmd *cmd)
{
	char	*str_pathname;
	char	**tmp_tab_pathname;
	char	*tab[2];

	if (ft_strchr(cmd->args[0], '/'))
	{
		tab[0] = cmd->args[0];
		tab[1] = NULL;
		str_pathname = is_valid_pathname(tab);
		return (str_pathname);
	}
	tmp_tab_pathname = make_pathname(shell, cmd);
	if (!tmp_tab_pathname)
		return (NULL);
	str_pathname = is_valid_pathname(tmp_tab_pathname);
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
	int	flags;
	int	std_fd;

	if (redirs->type == TOK_HEREDOC)
		return (apply_heredoc(redirs));
	flags = O_RDONLY;
	std_fd = 0;
	if (redirs->type == TOK_REDIR_OUT)
	{
		flags = O_WRONLY | O_TRUNC | O_CREAT;
		std_fd = 1;
	}
	else if (redirs->type == TOK_APPEND)
	{
		flags = O_WRONLY | O_APPEND | O_CREAT;
		std_fd = 1;
	}
	fd = open(redirs->file, flags, 0644);
	if (fd == -1)
		return (print_error(redirs->file, strerror(errno)), -1);
	dup2(fd, std_fd);
	close(fd);
	return (0);
}
void	wait_all(t_shell *shell, t_cmd *cmd)
{
	int	status;
	int	sig;

	status = 0;
	sig = 0;
	while (cmd)
	{
		waitpid(cmd->pid, &status, 0);
		if (WIFEXITED(status))
			shell->exit_status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
		{
			shell->exit_status = 128 + WTERMSIG(status);
			sig = WTERMSIG(status);
		}
		cmd = cmd->next;
	}
	if (sig == SIGINT)
		write(2, "\n", 1);
	else if (sig == SIGQUIT)
		write(2, "Quit (core dumped)\n", 19);
}
bool	setup_pipe(t_shell *shell, t_cmd *cmd, t_pipe *pipe_ctx)
{
	if (cmd->next)
	{
		if (pipe(pipe_ctx->pfd) == -1)
		{
			if (pipe_ctx->prev_pipe != -1)
				close(pipe_ctx->prev_pipe);
			perror("minishell: pipe");
			shell->exit_status = 1;
			return (false);
		}
	}
	return (true);
}