/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 15:33:13 by codespace         #+#    #+#             */
/*   Updated: 2026/04/17 13:47:30 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**create_tab_cmd(char *str, char **str_cmd)
{
	char	**tab_cmd;

	*str_cmd = readline(str);
	if (!*str_cmd)
		return (NULL);
	tab_cmd = ft_split(*str_cmd, ' ');
	if (!tab_cmd)
		return (NULL);
	return (tab_cmd);
}
void	ft_free(char **tab_str)
{
	int	i;

	i = 0;
	if (tab_str && *tab_str)
	{
		while (tab_str[i])
			free(tab_str[i++]);
	}
}
int	minishell(char **envp)
{
	char	**tab_cmd;
	char	*str_cmd;

	str_cmd = NULL;
	while (1)
	{
		tab_cmd = create_tab_cmd("minishell> ", &str_cmd);
		if (!tab_cmd)
			return (0);
		if (tab_cmd && *tab_cmd)
			add_history(str_cmd);
		if (g_signal == 0)
		{
			if (str_cmd && *str_cmd)
				handle_cmd_run(tab_cmd, envp);
		}
		free(str_cmd);
		ft_free(tab_cmd);
		g_signal = 0;
	}
	return (1);
}
int	run_builtin(char **tab_cmd, char **envp)
{
	if (ft_strchr(tab_cmd[0], '/'))
	{
		
	}
}

int	builtout(char **tab_cmd)
{

}
bool	is_it_builtout(char **tab_cmd)
{
	if (!(ft_strcmp(tab_cmd[0], "echo") && ft_strcmp(tab_cmd[0], "cd")
			&& ft_strcmp(tab_cmd[0], "pwd") && ft_strcmp(tab_cmd[0], "Export")
			&& ft_strcmp(tab_cmd[0], "unset") && ft_strcmp(tab_cmd[0], "env")
			&& ft_strcmp(tab_cmd[0], "exit")))
		return (true);
	return (false);
}
int	handle_cmd_run(char **tab_cmd, char **envp)
{
	if (is_it_builtout(tab_cmd))
	{
		run_builtout(tab_cmd);
	}
	else
	{
		run_builtin(tab_cmd, envp);
	}
}