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
	t_cmd	*cmds;

	token = lex(shell, line);
	if (!token)
	{
		gc_free(shell);
		return ;
	}
	if (syntax_check(token))
	{
		shell->exit_status = 2;
		gc_free(shell);
		return ;
	}
	cmds = parse(shell, token);
	if (cmds)
		cmds = expand(cmds, shell);
	debug_print_cmds(cmds);
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
