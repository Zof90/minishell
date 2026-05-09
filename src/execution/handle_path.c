/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zof <zof@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/09 16:04:29 by zof               #+#    #+#             */
/*   Updated: 2026/05/09 18:36:45 by zof              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gc.h"
#include "minishell.h"

size_t	calculate_len(char **tab_path)
{
	size_t	len;

	len = 0;
	while (tab_path[len])
		len++;
	return (len);
}
static char	*find_path_util(t_env *env)
{
	while (env)
	{
		if (!ft_strcmp(env->key, "PATH"))
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

static char	**find_path(t_shell *shell)
{
	char	**tab_path;
	char	*str_path;

	str_path = find_path_util(shell->env);
	if (!str_path)
		return (NULL);
	tab_path = gc_split(shell, str_path, ':');
	if (!tab_path)
		return (NULL);
	return (tab_path);
}
char	**make_pathname(t_shell *shell, t_cmd *cmd)
{
	int		i;
	char	**tab_path;
	char	**tab_pathname;
	size_t	len;
	char	*name;

	i = 0;
	name = gc_strjoin(shell, "/", cmd->args[0]);
	if (!name)
		return (NULL);
	tab_path = find_path(shell);
	if (!tab_path)
		return (NULL);
	len = calculate_len(tab_path);
	tab_pathname = gc_malloc(shell, sizeof(char *) * (len + 1));
	if (!tab_pathname)
		return (NULL);
	tab_pathname[len] = 0;
	while (tab_path[i])
	{
		tab_pathname[i] = gc_strjoin(shell, tab_path[i], name);
		if (!tab_pathname[i++])
			return (NULL);
	}
	return (tab_pathname);
}
char	*test_pathname(char **tab_pathname)
{
	int	i;

	i = 0;
	while (tab_pathname[i])
	{
		if (!access(tab_pathname[i], X_OK))
			return (tab_pathname[i]);
		i++;
	}
	return (NULL);
}
