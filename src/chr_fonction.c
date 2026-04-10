/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chr_fonction.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 12:55:02 by codespace         #+#    #+#             */
/*   Updated: 2026/04/10 13:25:01 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
char	**find_path(t_env *lst_env)
{
	char **tab_path;
	char *str_path;

	str_path = find_path_util(str_path);
	if (!str_path)
		return (NULL);
	tab_path = ft_split(str_path, ':');
	if (!tab_path)
		return (NULL);
	return (tab_path);
}