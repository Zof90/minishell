/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zof <zof@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/18 13:07:20 by azaytsev          #+#    #+#             */
/*   Updated: 2026/05/15 13:11:26 by zof              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_error(const char *context, const char *message)
{
	ft_putstr_fd("minishell: ", 2);
	if (context)
	{
		ft_putstr_fd((char *)context, 2);
		ft_putstr_fd(": ", 2);
	}
	ft_putendl_fd((char *)message, 2);
}

static int	has_search_path(t_shell *shell)
{
	char	*path_env;

	path_env = env_get(shell->env, "PATH");
	if (!path_env || !*path_env)
		return (0);
	return (1);
}

static int	probe_path(const char *name)
{
	struct stat	st;

	if (stat(name, &st) != 0)
		return (0);
	if (S_ISDIR(st.st_mode))
		return (print_error(name, "Is a directory"), 126);
	if (access(name, X_OK) != 0)
		return (print_error(name, "Permission denied"), 126);
	print_error(name, strerror(errno));
	return (126);
}

void	child_exit_error(t_shell *shell, char *name)
{
	int	code;

	if (ft_strchr(name, '/') || !has_search_path(shell))
	{
		code = probe_path(name);
		if (code)
			exit(code);
		print_error(name, "No such file or directory");
		exit(127);
	}
	print_error(name, "command not found");
	exit(127);
}
