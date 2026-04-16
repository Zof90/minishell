/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 12:55:02 by codespace         #+#    #+#             */
/*   Updated: 2026/04/16 11:32:57 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t	calculate_len(char **tab_path)
{
	size_t	len;

	len = 0;
	while (tab_path[len])
		len++;
	return (len);
}
static char	*find_path_util(t_env *lst_env)
{
	while (lst_env)
	{
		if (!ft_strcmp(lst_env->key, "PATH"))
			return (lst_env->value);
		lst_env = lst_env->next;
	}
	return (NULL);
}
static char	**find_path(t_env *lst_env)
{
	char	**tab_path;
	char	*str_path;

	str_path = find_path_util(lst_env);
	if (!str_path)
		return (NULL);
	tab_path = ft_split(str_path, ':');
	if (!tab_path)
		return (NULL);
	return (tab_path);
}
char	**make_pathname(t_env *lst_env, char *name)
{
	int		i;
	char	**tab_pathname;
	char	**tab_path;
	size_t	len;

	i = 0;
	tab_path = find_path(lst_env);
	if (!tab_path)
		return (NULL);
	len = calculate_len(tab_path);
	tab_pathname = malloc(sizeof(char *) * (len + 1));
	if (!tab_pathname)
		return (NULL);
	tab_pathname[len] = 0;
	while (tab_path[i])
	{
		tab_pathname[i] = ft_strjoin(tab_path[i], name);
		i++;
	}
	return (tab_pathname);
}
char	*find_pathname(char **tab_pathname)
{
	int	i;

	i = 0;
	while (tab_pathname[i])
	{
		if (!access(tab_pathname[i], X_OK))
		{
			return (tab_pathname[i]);
		}
		i++;
	}
	return (NULL);
}
/// bin/usr/commande(ls...)