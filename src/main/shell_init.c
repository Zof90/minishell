/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zof <zof@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 09:00:00 by azaytsev          #+#    #+#             */
/*   Updated: 2026/05/01 13:49:57 by zof              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	init_shell(t_shell *shell, int argc, char **argv, char **envp)
{
	(void)argv;
	if (argc > 1)
	{
		print_error(NULL, "arguments not supported");
		return (0);
	}
	shell->env = env_init(envp);
	if (!shell->env)
	{
		print_error(NULL, "failed to initialize environment");
		return (0);
	}
	shell->gc = NULL;
	shell->exit_status = 0;
	shell->running = 1;
	return (1);
}
