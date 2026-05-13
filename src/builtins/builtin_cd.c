/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azaytsev <azaytsev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/13 09:00:00 by azaytsev          #+#    #+#             */
/*   Updated: 2026/05/13 09:00:00 by azaytsev         ###   ########.fr       */
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

static const char	*resolve_target(t_shell *shell, char **args, int *print)
{
	const char	*target;

	*print = 0;
	if (!args[1] || !ft_strncmp(args[1], "~", 2))
	{
		target = env_get(shell->env, "HOME");
		if (!target)
		{
			print_error("cd", "HOME not set");
			return (NULL);
		}
		return (target);
	}
	if (!ft_strncmp(args[1], "-", 2))
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
	return (args[1]);
}

static int	update_pwd_pair(t_shell *shell, char *old_pwd)
{
	char	*new_pwd;
	int		ret;

	ret = 0;
	if (old_pwd && env_set(&shell->env, "OLDPWD", old_pwd))
		ret = 1;
	new_pwd = getcwd(NULL, 0);
	if (new_pwd)
	{
		if (env_set(&shell->env, "PWD", new_pwd))
			ret = 1;
		free(new_pwd);
	}
	return (ret);
}

int	builtin_cd(t_shell *shell, char **args)
{
	const char	*target;
	char		*old_pwd;
	int			print;

	if (args[1] && args[2])
	{
		print_error("cd", "too many arguments");
		return (1);
	}
	target = resolve_target(shell, args, &print);
	if (!target)
		return (1);
	old_pwd = getcwd(NULL, 0);
	if (chdir(target) != 0)
	{
		free(old_pwd);
		return (cd_error(target, errno));
	}
	if (print)
		ft_putendl_fd((char *)target, 1);
	update_pwd_pair(shell, old_pwd);
	free(old_pwd);
	return (0);
}
