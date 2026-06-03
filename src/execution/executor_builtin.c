/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_builtin.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schouite <schouite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/12 14:18:58 by schouite          #+#    #+#             */
/*   Updated: 2026/05/18 10:36:42 by schouite         ###   ########.fr       */
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

static void	restore_std(t_cmd *header, int fd_in, int fd_out, t_redir *redirs)
{
	if (!header->next)
	{
		if (dup2(fd_in, 0) == -1)
			print_error("dup2", strerror(errno));
		if (dup2(fd_out, 1) == -1)
			print_error("dup2", strerror(errno));
		close(fd_in);
		close(fd_out);
	}
	reap_heredoc_writers(redirs);
}

int	run_builtin(t_shell *shell, t_cmd *cmd, t_cmd *header)
{
	int		fd_in;
	int		fd_out;
	t_redir	*redir;

	if (header->next)
	{
		dispatch_builtin(shell, cmd);
		exit(shell->exit_status);
	}
	if (save_std(&fd_in, &fd_out) == -1)
		return (shell->exit_status = 1, 1);
	redir = cmd->redirs;
	while (redir)
	{
		if (redir_builtin(redir) == -1)
		{
			restore_std(header, fd_in, fd_out, cmd->redirs);
			return (shell->exit_status = 1, 1);
		}
		redir = redir->next;
	}
	dispatch_builtin(shell, cmd);
	restore_std(header, fd_in, fd_out, cmd->redirs);
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
