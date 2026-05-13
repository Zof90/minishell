/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_print.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azaytsev <azaytsev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/13 09:00:00 by azaytsev          #+#    #+#             */
/*   Updated: 2026/05/13 09:00:00 by azaytsev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_env	**collect_env(t_env *env, int *count)
{
	t_env	**arr;
	int		i;

	*count = env_size(env);
	arr = malloc(sizeof(t_env *) * (*count + 1));
	if (!arr)
		return (NULL);
	i = 0;
	while (env)
	{
		arr[i++] = env;
		env = env->next;
	}
	arr[i] = NULL;
	return (arr);
}

static void	sort_env(t_env **arr, int n)
{
	int		i;
	int		j;
	t_env	*tmp;

	i = 0;
	while (i < n - 1)
	{
		j = 0;
		while (j < n - 1 - i)
		{
			if (ft_strncmp(arr[j]->key, arr[j + 1]->key,
					ft_strlen(arr[j]->key) + 1) > 0)
			{
				tmp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = tmp;
			}
			j++;
		}
		i++;
	}
}

static void	print_node(t_env *node)
{
	ft_putstr_fd("declare -x ", 1);
	ft_putstr_fd(node->key, 1);
	if (node->value)
	{
		ft_putstr_fd("=\"", 1);
		ft_putstr_fd(node->value, 1);
		ft_putendl_fd("\"", 1);
	}
	else
		ft_putendl_fd("", 1);
}

int	export_print(t_shell *shell)
{
	t_env	**arr;
	int		count;
	int		i;

	arr = collect_env(shell->env, &count);
	if (!arr)
		return (1);
	sort_env(arr, count);
	i = 0;
	while (arr[i])
	{
		print_node(arr[i]);
		i++;
	}
	free(arr);
	return (0);
}
