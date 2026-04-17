/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 15:03:11 by codespace         #+#    #+#             */
/*   Updated: 2026/04/14 12:08:05 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	executor(t_shell *node_shell, char **tab_cmd, char *str_pathname,
		char **envp)
{
	pid_t	pid;
	int		status;

	status = 0;
	pid = fork();
	if (pid == 0)
	{
		execve(str_pathname, tab_cmd, envp);
		perror("minishell: execve");
		exit(1);
	}
	else if (pid > 0)
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			node_shell->exit_status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			node_shell->exit_status = WTERMSIG(status);
	}
}

bool	run_command(char **tab_cmd, char **envp)
{
	t_shell *node_shell;
	char **tab_pathname;
	char *str_pathname;
	char *sep_str_cmd;

	sep_str_cmd = ft_strjoin("/", tab_cmd[0]);
	if (!sep_str_cmd)
		return (false);
	node_shell = fill_shell(envp);
	if (!node_shell)
		return (false);
	tab_pathname = make_pathname(node_shell->env, sep_str_cmd);
	if (!tab_pathname)
		return (false);
	str_pathname = find_pathname(tab_pathname);
	if (!str_pathname)
		return (false);
	executor(node_shell, tab_cmd, str_pathname, envp);
	return (true);
}