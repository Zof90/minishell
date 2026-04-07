/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 15:33:13 by codespace         #+#    #+#             */
/*   Updated: 2026/04/06 18:10:36 by codespace        ###   ########.fr       */
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

int	minishell(int argc, char **argv, char **envp)
{
	char	*line;

	(void)argv;
	(void)argc;
	while (1)
	{
		line = readline("minishell> ");
		if (!line)
			return (0);
		if (line && *line)
			add_history(line);
		if (g_signal == 0)
		{
			executor(envp);
		}
		free(line);
		g_signal = 0;
	}
	return (1);
}
