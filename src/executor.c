/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 15:03:11 by codespace         #+#    #+#             */
/*   Updated: 2026/04/12 10:34:58 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	executor(t_shell *node_shell, char **tab_pahtname, char *str_pathname,
		char **envp)
{
	pid_t pid;
	int status;

	status = 0;
	pid = fork();
	if (pid == 0)
	{
		execve(str_pathname, tab_pahtname, envp);
		perror("minishell: execve");
		exit(1);
	}
	else if (pid > 0)
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
		{
			node_shell->exit_status = WEXITSTATUS(status);
		}
		
	}
}