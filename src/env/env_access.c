/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_access.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azaytsev <azaytsev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/12 10:03:58 by azaytsev          #+#    #+#             */
/*   Updated: 2026/04/12 10:04:00 by azaytsev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*env_get(t_env *env, const char *key)
{
	size_t	len;

	len = ft_strlen(key) + 1;
	while (env)
	{
		if (ft_strncmp(env->key, key, len) == 0)
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

static int	env_update(t_env *env, const char *key, const char *value)
{
	size_t	len;
	char	*new_val;

	len = ft_strlen(key) + 1;
	while (env)
	{
		if (ft_strncmp(env->key, key, len) == 0)
		{
			new_val = ft_strdup(value);
			if (!new_val)
				return (-1);
			free(env->value);
			env->value = new_val;
			return (1);
		}
		env = env->next;
	}
	return (0);
}

int	env_set(t_env **env, const char *key, const char *value)
{
	int		found;
	t_env	*node;

	found = env_update(*env, key, value);
	if (found == -1)
		return (1);
	if (found == 1)
		return (0);
	node = env_new_node(key, value);
	if (!node)
		return (1);
	env_add_back(env, node);
	return (0);
}

int	env_unset(t_env **env, const char *key)
{
	t_env	*cur;
	t_env	*prev;
	size_t	len;

	len = ft_strlen(key) + 1;
	prev = NULL;
	cur = *env;
	while (cur)
	{
		if (ft_strncmp(cur->key, key, len) == 0)
		{
			if (prev)
				prev->next = cur->next;
			else
				*env = cur->next;
			free(cur->key);
			free(cur->value);
			free(cur);
			return (0);
		}
		prev = cur;
		cur = cur->next;
	}
	return (0);
}
