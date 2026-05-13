/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_util.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zof <zof@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/12 14:18:58 by zof               #+#    #+#             */
/*   Updated: 2026/05/13 20:01:55 by zof              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_builtin(t_cmd *cmd)
{
	if (ft_strcmp(cmd->args[0], "echo") == 0)
		return (true);
	if (ft_strcmp(cmd->args[0], "cd") == 0)
		return (true);
	if (ft_strcmp(cmd->args[0], "pwd") == 0)
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
static int	redir_builtin(t_cmd *cmd)
{
	int	fd;
	int	fd_backup;

	fd = -1;
	fd_backup = dup(1);
	fd = run_redir(cmd->redirs, fd);
	if (fd == -1)
		return (close(fd_backup), -1);
	return (fd_backup);
}
int	run_builtin(t_shell *shell, t_cmd *cmd, t_cmd *header)
{
	int	fd_backup;

	fd_backup = -1;
	if (!header->next && cmd->redirs)
	{
		fd_backup = redir_builtin(cmd);
		if (fd_backup == -1)
			return (1);
	}
	if (!ft_strcmp(cmd->args[0], "echo"))
		shell->exit_status = builtin_echo(shell, cmd->args);
	else if (!ft_strcmp(cmd->args[0], "env"))
		shell->exit_status = builtin_env(shell, cmd->args);
	else if (!ft_strcmp(cmd->args[0], "pwd"))
		shell->exit_status = builtin_pwd(shell, cmd->args);
	// else if (!ft_strcmp(cmd->args[0], "cd"))
	// 	shell->exit_status = builtin_cd(shell, cmd->args);
	// else if (!ft_strcmp(cmd->args[0], "export"))
	// 	shell->exit_status = builtin_export(shell, cmd->args);
	// else if (!ft_strcmp(cmd->args[0], "unset"))
	// 	shell->exit_status = builtin_unset(shell, cmd->args);
	// else if (!ft_strcmp(cmd->args[0], "exit"))
	// 	shell->exit_status = builtin_exit(shell, cmd->args);
	if (fd_backup != -1)
	{
		dup2(fd_backup, 1);
		close(fd_backup);
	}
	if (!header->next)
		return (shell->exit_status);
	exit(shell->exit_status);
}

bool	handle_executor(t_shell *shell, t_cmd *cmd)
{
	t_cmd *header;

	header = cmd;
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