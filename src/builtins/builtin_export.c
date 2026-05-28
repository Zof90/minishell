/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azaytsev <azaytsev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/13 09:00:00 by azaytsev          #+#    #+#             */
/*   Updated: 2026/05/13 09:00:00 by azaytsev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_valid_identifier(const char *s)
{
	int	i;

	if (!s || !s[0])
		return (0);
	if (!ft_isalpha(s[0]) && s[0] != '_')
		return (0);
	i = 1;
	while (s[i] && s[i] != '=')
	{
		if (!ft_isalnum(s[i]) && s[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

static int	export_invalid(const char *arg)
{
	ft_putstr_fd("minishell: export: `", 2);
	ft_putstr_fd((char *)arg, 2);
	ft_putendl_fd("': not a valid identifier", 2);
	return (1);
}

static int	export_assign(t_shell *shell, const char *arg)
{
	char	*eq;
	char	*key;
	int		ret;

	eq = ft_strchr((char *)arg, '=');
	if (!eq)
		return (0);
	key = ft_substr(arg, 0, eq - arg);
	if (!key)
		return (1);
	ret = env_set(&shell->env, key, eq + 1);
	free(key);
	return (ret);
}

static int	export_invalid_option(const char *arg)
{
	ft_putstr_fd("minishell: export: ", 2);
	ft_putstr_fd((char *)arg, 2);
	ft_putendl_fd(": invalid option", 2);
	ft_putendl_fd("export: usage: export [name[=value] ...]", 2);
	return (2);
}

int	builtin_export(t_shell *shell, char **args)
{
	int	i;
	int	status;

	if (!args[1])
		return (export_print(shell));
	if (args[1][0] == '-')
		return (export_invalid_option(args[1]));
	status = 0;
	i = 1;
	while (args[i])
	{
		if (!is_valid_identifier(args[i]))
			status = export_invalid(args[i]);
		else if (export_assign(shell, args[i]))
			status = 1;
		i++;
	}
	return (status);
}
