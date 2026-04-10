/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 15:03:11 by codespace         #+#    #+#             */
/*   Updated: 2026/04/10 12:43:57 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void	executor(char **envp)
{
	pid_t	pid;
	char	*args[] = {"/bin/ls", NULL};
	int		status;
	int		exit_code;

    exit_code = 0;
	status = 0;
	pid = fork();
	if (pid == 0)
	{
		execve(args[0], args, envp);
		perror("minishell: execve");
		exit(1);
	}
	else if (pid > 0)
	{
		waitpid(pid, &status, 0);
        if (WIFEXITED(status))
        {
            exit_code = WEXITSTATUS(status);
        }
	}
}