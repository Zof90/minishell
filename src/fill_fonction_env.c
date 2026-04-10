/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_fonction_env.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 12:42:20 by codespace         #+#    #+#             */
/*   Updated: 2026/04/10 12:43:13 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	char_chr(char *path)
{
	int	i;

	while (path[i])
	{
		if (path[i] = '=')
		{
			return (i);
		}
		i++;
	}
	return (0);
}
static char	*handle_envp_value(char *path, int pos)
{
	char	*value;

	value = ft_strdup(path + pos);
	if (!value)
		return (NULL);
	return (value);
}
static char	*handle_envp_key(char *path, int pos)
{
	char	*key;

	key = ft_substr(path, 0, pos);
	if (!key)
		return (NULL);
	return (key);
}
static t_env	*fill_envp(char **envp)
{
	int		i;
	int		pos;
	t_env	*lst_node;
	t_env	*new_node;

	i = 0;
	lst_node = NULL;
	while (envp[i])
	{
		pos = char_chr(envp[i]);
		new_node = env_node(handle_envp_key(envp[i], pos),
				handle_envp_value(envp[i], pos));
		if (!new_node)
			return (NULL);
		ft_lstadd_back(&lst_node, new_node);
		i++;
	}
	return (lst_node);
}
t_shell	*fill_shell(char **envp)
{
	t_env *lst_env;
	t_shell *lst_shell;

	lst_env = fill_envp(envp);
	if (lst_env)
		return (NULL);
	lst_shell = malloc(sizeof(t_shell));
	if (!lst_shell)
		return (NULL);
	lst_shell->env = lst_env;
	return (lst_shell);
}