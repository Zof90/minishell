/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azaytsev <azaytsev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 09:39:49 by azaytsev          #+#    #+#             */
/*   Updated: 2026/04/28 09:44:56 by azaytsev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_pwd(t_shell *shell, char **args)
{
	char	*cwd;
	char	*pwd;

	(void)args;
	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		pwd = env_get(shell->env, "PWD");
		if (pwd)
		{
			ft_putendl_fd(pwd, 1);
			return (0);
		}
		print_error("pwd", "error retrieving current directory");
		return (1);
	}
	ft_putendl_fd(cwd, 1);
	free(cwd);
	return (0);
}
