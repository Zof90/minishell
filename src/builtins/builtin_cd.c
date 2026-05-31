/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azaytsev <azaytsev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/13 09:00:00 by azaytsev          #+#    #+#             */
/*   Updated: 2026/05/24 21:30:00 by azaytsev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <errno.h>
#include <string.h>

static int	cd_error(const char *target, int err)
{
	ft_putstr_fd("minishell: cd: ", 2);
	ft_putstr_fd((char *)target, 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(strerror(err), 2);
	return (1);
}

static const char	*resolve_target(t_shell *shell, const char *arg, int *print)
{
	const char	*target;

	*print = 0;
	if (!arg || !ft_strncmp(arg, "~", 2))
	{
		target = env_get(shell->env, "HOME");
		if (!target)
		{
			print_error("cd", "HOME not set");
			return (NULL);
		}
		return (target);
	}
	if (!ft_strncmp(arg, "-", 2))
	{
		target = env_get(shell->env, "OLDPWD");
		if (!target)
		{
			print_error("cd", "OLDPWD not set");
			return (NULL);
		}
		*print = 1;
		return (target);
	}
	return (arg);
}

static int	update_pwd_pair(t_shell *shell, char *old, const char *target)
{
	char	*new_pwd;
	char	*logical;
	int		ret;

	new_pwd = getcwd(NULL, 0);
	logical = NULL;
	if (!new_pwd)
		logical = cd_curpath(shell, target);
	ret = 0;
	if (old && env_set(&shell->env, "OLDPWD", old))
		ret = 1;
	if (new_pwd)
	{
		if (env_set(&shell->env, "PWD", new_pwd))
			ret = 1;
		free(new_pwd);
		return (ret);
	}
	ft_putstr_fd("minishell: cd: error retrieving current directory: ", 2);
	ft_putstr_fd("getcwd: cannot access parent directories: ", 2);
	ft_putendl_fd("No such file or directory", 2);
	if (env_set(&shell->env, "PWD", logical))
		ret = 1;
	return (ret);
}

static int	cd_options(char **args, int *target_idx)
{
	*target_idx = 1;
	if (!args[1])
		return (0);
	if (!ft_strcmp(args[1], "--"))
	{
		*target_idx = 2;
		return (0);
	}
	if (!ft_strcmp(args[1], "-") || args[1][0] != '-')
		return (0);
	ft_putstr_fd("minishell: cd: ", 2);
	ft_putstr_fd(args[1], 2);
	ft_putendl_fd(": invalid option", 2);
	ft_putendl_fd("cd: usage: cd [dir]", 2);
	return (-1);
}

int	builtin_cd(t_shell *shell, char **args)
{
	const char	*target;
	char		*old;
	int			print;
	int			idx;

	if (cd_options(args, &idx) == -1)
		return (2);
	if (args[idx] && args[idx + 1])
		return (print_error("cd", "too many arguments"), 1);
	target = resolve_target(shell, args[idx], &print);
	if (!target)
		return (1);
	if (target[0] == '\0')
		return (0);
	old = env_get(shell->env, "PWD");
	if (chdir(target) != 0)
		return (cd_error(target, errno));
	if (print)
		ft_putendl_fd((char *)target, 1);
	return (update_pwd_pair(shell, old, target));
}
