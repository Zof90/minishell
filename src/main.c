/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schouite <schouite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/18 13:07:20 by azaytsev          #+#    #+#             */
/*   Updated: 2026/04/21 18:22:57 by schouite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "gc.h"

volatile sig_atomic_t	g_signal = 0;

static void	shell_loop(t_shell *shell)
{
	char	*line;

	while (shell->running)
	{
		line = readline("minishell> ");
		if (g_signal)
		{
			shell->exit_status = 130;
			g_signal = 0;
		}
		if (!line)
		{
			ft_putendl_fd("exit", 1);
			break ;
		}
		if (*line)
			add_history(line);
		free(line);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	shell;

	(void)argc;
	(void)argv;
	shell.gc = NULL;
	shell.env = env_init(envp);
	shell.exit_status = 0;
	shell.running = 1;
	setup_signals_interactive();
	shell_loop(&shell);
	free_env(shell.env);
	return (shell.exit_status);
}
