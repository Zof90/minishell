/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_builtin.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zof <zof@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/12 14:18:58 by zof               #+#    #+#             */
/*   Updated: 2026/05/18 10:36:42 by zof              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	redir_builtin(t_redir *redir)
{
	int	fd;

	fd = -1;
	fd = run_redir(redir, fd);
	if (fd == -1)
		return (-1);
	return (0);
}

static void	dispatch_builtin(t_shell *shell, t_cmd *cmd)
{
	if (!ft_strcmp(cmd->args[0], "echo"))
		shell->exit_status = builtin_echo(shell, cmd->args);
	else if (!ft_strcmp(cmd->args[0], "env"))
		shell->exit_status = builtin_env(shell, cmd->args);
	else if (!ft_strcmp(cmd->args[0], "pwd"))
		shell->exit_status = builtin_pwd(shell, cmd->args);
	else if (!ft_strcmp(cmd->args[0], "cd"))
		shell->exit_status = builtin_cd(shell, cmd->args);
	else if (!ft_strcmp(cmd->args[0], "export"))
		shell->exit_status = builtin_export(shell, cmd->args);
	else if (!ft_strcmp(cmd->args[0], "unset"))
		shell->exit_status = builtin_unset(shell, cmd->args);
	else if (!ft_strcmp(cmd->args[0], "exit"))
		shell->exit_status = builtin_exit(shell, cmd->args);
}

static void	restore_std(t_cmd *header, int fd_in, int fd_out)
{
	if (!header->next)
	{
		dup2(fd_in, 0);
		dup2(fd_out, 1);
		close(fd_in);
		close(fd_out);
	}
}

int	run_builtin(t_shell *shell, t_cmd *cmd, t_cmd *header)
{
	int		fd_in;
	int		fd_out;
	int		ret;
	t_redir	*redir;

	redir = cmd->redirs;
	fd_in = dup(0);
	fd_out = dup(1);
	while (!header->next && redir)
	{
		ret = redir_builtin(redir);
		if (ret == -1)
		{
			dup2(fd_in, 0);
			dup2(fd_out, 1);
			shell->exit_status = 1;
			return (close(fd_in), close(fd_out), 1);
		}
		redir = redir->next;
	}
	dispatch_builtin(shell, cmd);
	if (header->next)
		exit(shell->exit_status);
	restore_std(header, fd_in, fd_out);
	return (shell->exit_status);
}

bool	handle_executor(t_shell *shell, t_cmd *cmd)
{
	t_cmd	*header;

	header = cmd;
	if (!cmd->next && (!cmd->args || !cmd->args[0]))
	{
		run_noargs(shell, cmd);
		return (true);
	}
	if (!cmd->next && is_builtin(cmd))
	{
		run_builtin(shell, cmd, header);
		if (shell->exit_status != 0)
			return (false);
		return (true);
	}
	run_executor(shell, cmd);
	return (true);
}
