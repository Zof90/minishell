/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azaytsev <azaytsev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/12 10:04:19 by azaytsev          #+#    #+#             */
/*   Updated: 2026/04/12 10:04:21 by azaytsev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*env_init(char **envp)
{
	t_env	*env;
	t_env	*node;
	char	*eq;
	char	*key;

	env = NULL;
	while (*envp)
	{
		eq = ft_strchr(*envp, '=');
		if (eq)
		{
			key = ft_substr(*envp, 0, eq - *envp);
			if (key)
			{
				node = env_new_node(key, eq + 1);
				free(key);
				if (node)
					env_add_back(&env, node);
			}
		}
		envp++;
	}
	return (env);
}
