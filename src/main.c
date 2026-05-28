/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zof <zof@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/18 13:07:20 by azaytsev          #+#    #+#             */
/*   Updated: 2026/05/21 13:26:33 by zof              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	g_signal = 0;

int	main(int argc, char **argv, char **envp)
{
	t_shell	shell;

	if (!init_shell(&shell, argc, argv, envp))
		return (1);
	setup_signals_interactive();
	shell_loop(&shell);
	cleanup_shell(&shell);
	return (shell.exit_status);
}
