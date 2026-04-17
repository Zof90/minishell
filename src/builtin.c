/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 14:38:30 by codespace         #+#    #+#             */
/*   Updated: 2026/04/16 15:51:55 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_echo(char **msg)
{
	int	i;

	i = 1;
	while (msg[i])
		printf(msg[i++]);
}
void	ft_pwd(char *buff, size_t size)
{
	char *str;

	getcwd(buff, size);
}