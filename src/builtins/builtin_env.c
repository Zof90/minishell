/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azaytsev <azaytsev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 09:09:27 by azaytsev          #+#    #+#             */
/*   Updated: 2026/04/28 09:14:34 by azaytsev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_env(t_shell *shell, char **args)
{
	t_env	*cur;

	if (args[1])
	{
		print_error("env", "too many arguments");
		return (1);
	}
	cur = shell->env;
	while (cur)
	{
		if (cur->value)
		{
			ft_putstr_fd(cur->key, 1);
			ft_putchar_fd('=', 1);
			ft_putendl_fd(cur->value, 1);
		}
		cur = cur->next;
	}
	return (0);
}
