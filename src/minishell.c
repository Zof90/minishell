/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 15:33:13 by codespace         #+#    #+#             */
/*   Updated: 2026/04/13 16:22:59 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	minishell(int argc, char **argv, char **envp)
{
	char	*line;

	(void)argc;
	(void)argv;
	while (1)
	{
		line = readline("minishell> ");
		if (!line)
			return (0);
		if (line && *line)
			add_history(line);
		if (g_signal == 0)
		{
			if (line && *line)
				run_command(line, envp);
		}
		free(line);
		g_signal = 0;
	}
	return (1);
}
