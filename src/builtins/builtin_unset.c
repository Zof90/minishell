/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azaytsev <azaytsev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 09:00:00 by azaytsev          #+#    #+#             */
/*   Updated: 2026/04/28 09:00:00 by azaytsev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_valid_id(const char *s)
{
	int	i;

	if (!s || !s[0] || (!ft_isalpha(s[0]) && s[0] != '_'))
		return (0);
	i = 1;
	while (s[i])
	{
		if (!ft_isalnum(s[i]) && s[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

static int	unset_invalid(const char *name)
{
	ft_putstr_fd("minishell: unset: `", 2);
	ft_putstr_fd((char *)name, 2);
	ft_putendl_fd("': not a valid identifier", 2);
	return (1);
}

int	builtin_unset(t_shell *shell, char **args)
{
	int	i;
	int	status;

	status = 0;
	i = 1;
	while (args[i])
	{
		if (!is_valid_id(args[i]))
			status = unset_invalid(args[i]);
		else
			env_unset(&shell->env, args[i]);
		i++;
	}
	return (status);
}
