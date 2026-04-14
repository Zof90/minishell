/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 15:33:13 by codespace         #+#    #+#             */
/*   Updated: 2026/04/14 11:44:42 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**handle_comnd(char *str, char *str_comnd)
{
	char	**tab_comnd;

	str_comnd = readline(str);
	if (!str_comnd)
		return (NULL);
	tab_comnd = ft_split(str_comnd, " ");
	if (!tab_comnd)
		return (NULL);
	return (tab_comnd);
}

int	minishell(int argc, char **argv, char **envp)
{
	char	**tab_comnd;
	char	*str_comnd;

	while (1)
	{
		tab_comnd = handle_comnd("minishell> ", str_comnd);
		if (!tab_comnd)
			return (0);
		if (tab_comnd && *tab_comnd)
			add_history(str_comnd);
		if (g_signal == 0)
		{
			if (str_comnd && *str_comnd)
				run_command(tab_comnd, envp);
		}
		free(str_comnd);
		g_signal = 0;
	}
	return (1);
}
