/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schouite <schouite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 09:23:31 by azaytsev          #+#    #+#             */
/*   Updated: 2026/05/01 13:49:57 by schouite         ###   ########.fr       */
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

static int	bump_shlvl(t_shell *shell)
{
	char	*old;
	char	*new_val;
	int		level;
	int		ret;

	old = env_get(shell->env, "SHLVL");
	level = 0;
	if (old)
		level = ft_atoi(old);
	level += 1;
	if (level < 0)
		level = 0;
	new_val = ft_itoa(level);
	if (!new_val)
		return (1);
	ret = env_set(&shell->env, "SHLVL", new_val);
	free(new_val);
	return (ret);
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
	if (bump_shlvl(shell))
		return (0);
	shell->exit_status = 0;
	shell->running = 1;
	return (1);
}
