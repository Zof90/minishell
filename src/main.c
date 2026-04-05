/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 19:42:23 by codespace         #+#    #+#             */
/*   Updated: 2026/04/05 17:34:34 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	g_signal = 0;

int	main(void)
{
	char *line;

	set_signal();
	while (1)
	{
		line = readline("minishell> ");
		if (!line)
			return (1);
		if (line && *line)
			add_history(line);
		if (g_signal == 0)
		{
		}
		free(line);
	}
}