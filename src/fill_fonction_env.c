/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_fonction_env.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 12:42:20 by codespace         #+#    #+#             */
/*   Updated: 2026/04/13 16:02:49 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t	char_chr(char *path)
{
	size_t	len;

	len = 0;
	while (path[len])
	{
		if (path[len] == '=')
			return (len);
		len++;
	}
	return (0);
}
static char	*handle_envp_value(char *path, int pos)
{
	char	*value;

	value = ft_strdup(path + pos + 1);
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
	size_t	pos;
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
		ft_env_lstadd_back(&lst_node, new_node);
		i++;
	}
	return (lst_node);
}
t_shell	*fill_shell(char **envp)
{
	t_env *lst_env;
	t_shell *node_shell;

	lst_env = fill_envp(envp);
	if (!lst_env)
		return (NULL);
	node_shell = malloc(sizeof(t_shell));
	if (!node_shell)
		return (NULL);
	node_shell->env = lst_env;
	return (node_shell);
}