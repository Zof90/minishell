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

static int	update_start_pwd(t_shell *shell)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (0);
	if (env_set(&shell->env, "PWD", cwd))
	{
		free(cwd);
		return (1);
	}
	free(cwd);
	return (0);
}

int	init_shell(t_shell *shell, int argc, char **argv, char **envp)
{
	(void)argv;
	if (argc > 1)
	{
		print_error(NULL, "arguments not supported");
		return (0);
	}
	shell->env = env_init(envp);
	shell->gc = NULL;
	if (update_start_pwd(shell))
		return (0);
	shell->exit_status = 0;
	shell->running = 1;
	return (1);
}
