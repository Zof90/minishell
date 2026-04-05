/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_fonctions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 14:36:38 by codespace         #+#    #+#             */
/*   Updated: 2026/04/05 17:39:19 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	sig_handler(int signal)
{
	g_signal = signal;
	rl_replace_line("", 0);
	rl_on_new_line();
	write(1, "\n", 1);
	rl_redisplay();
}

void	set_signal(void)
{
	struct sigaction	sig;

	ft_bzero(&sig, sizeof(sig));
	sigemptyset(&sig.sa_mask);
	sig.sa_flags = 0;
	sig.sa_handler = &sig_handler;
	sigaction(SIGINT, &sig, NULL);
}
