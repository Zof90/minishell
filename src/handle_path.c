/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 12:55:02 by codespace         #+#    #+#             */
/*   Updated: 2026/04/12 10:29:24 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	calculate_len(char **tab_path)
{
	int	i;

	i = 0;
	while (tab_path[i])
		i++;
	return (i);
}
static char	*find_path_util(t_env *lst_env)
{
	int	i;

	i = 0;
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

	str_path = find_path_util(str_path);
	if (!str_path)
		return (NULL);
	tab_path = ft_split(str_path, ':');
	if (!tab_path)
		return (NULL);
	return (tab_path);
}
static char	**make_pathname(t_env *lst_env, char *name)
{
	int		i;
	char	**tab_pathname;
	char	**tab_path;
	size_t	len;

	i = 0;
	len = calculate_len(tab_path);
	tab_path = find_path(lst_env);
	if (!tab_path)
		return (NULL);
	tab_pathname = malloc(sizeof(char *) * len + 1);
	if (tab_pathname)
		return (NULL);
	tab_pathname[len] = 0;
	while (tab_path[i])
	{
		tab_pathname[i] = ft_strjoin(tab_path[i], name);
		i++;
	}
	return (tab_pathname);
}
char	*find_pathname(t_env *lst_env, char *name)
{
	int		i;
	char	**tab_pathname;

	i = 0;
	tab_pathname = make_pathname(lst_env, name);
	if (!tab_pathname)
		return (NULL);
	while (tab_pathname[i])
	{
		if (!access(tab_pathname[i], X_OK))
			return (tab_pathname[i]);
		i++;
	}
	return (NULL);
}
/bin/usr/commande(ls...)