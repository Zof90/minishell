/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azaytsev <azaytsev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 09:46:10 by azaytsev          #+#    #+#             */
/*   Updated: 2026/04/28 09:51:17 by azaytsev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_unset(t_shell *shell, char **args)
{
	int	i;

	if (args[1] && args[1][0] == '-' && args[1][1] != '\0')
	{
		ft_putstr_fd("minishell: unset: ", 2);
		ft_putstr_fd(args[1], 2);
		ft_putendl_fd(": invalid option", 2);
		ft_putendl_fd("unset: usage: unset [name ...]", 2);
		return (2);
	}
	i = 1;
	while (args[i])
	{
		env_unset(&shell->env, args[i]);
		i++;
	}
	return (0);
}
