/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_loop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zof <zof@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 09:00:00 by azaytsev          #+#    #+#             */
/*   Updated: 2026/05/01 14:09:11 by zof              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gc.h"
#include "minishell.h"

static void	handle_signal_tick(t_shell *shell)
{
	if (g_signal == SIGINT)
	{
		shell->exit_status = 130;
		g_signal = 0;
	}
}

static char	*read_input(t_shell *shell)
{
	char	*line;

	line = readline("minishell> ");
	handle_signal_tick(shell);
	if (!line)
	{
		ft_putendl_fd("exit", 1);
		return (NULL);
	}
	if (*line)
		add_history(line);
	return (line);
}

static void	process_line(t_shell *shell, char *line)
{
	t_token	*token;

	(void)shell;
	(void)line;
	token = lex(shell, line);
	debug_print_tokens(token);
	gc_free(shell);
}

void	shell_loop(t_shell *shell)
{
	char	*line;

	while (shell->running)
	{
		line = read_input(shell);
		if (!line)
			break ;
		if (*line)
			process_line(shell, line);
		free(line);
	}
}
