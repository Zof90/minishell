/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_loop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zof <zof@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 09:00:00 by azaytsev          #+#    #+#             */
/*   Updated: 2026/05/18 15:49:44 by zof              ###   ########.fr       */
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
	int		tty;

	tty = isatty(STDIN_FILENO);
	if (tty)
		line = readline("minishell> ");
	else
		line = read_line_fd(STDIN_FILENO);
	handle_signal_tick(shell);
	if (!line)
	{
		if (tty)
			ft_putendl_fd("exit", 1);
		return (NULL);
	}
	if (tty && *line)
		add_history(line);
	return (line);
}

static int	is_runnable(t_shell *shell, t_token *token, t_cmd **out)
{
	if (!token)
		return (shell->exit_status = 2, 0);
	if (syntax_check(token))
		return (shell->exit_status = 2, 0);
	*out = parse(shell, token);
	if (*out)
		*out = expand(*out, shell);
	if (*out && collect_heredocs(*out, shell))
		return (shell->exit_status = 130, 0);
	return (1);
}

static void	process_line(t_shell *shell, char *line)
{
	t_token	*token;
	t_cmd	*cmds;

	cmds = NULL;
	token = lex(shell, line);
	if (is_runnable(shell, token, &cmds) && cmds)
		handle_executor(shell, cmds);
	gc_free(shell);
}

void	shell_loop(t_shell *shell)
{
	char	*line;
	int		i;

	while (shell->running)
	{
		line = read_input(shell);
		if (!line)
			break ;
		i = 0;
		while (line[i] == ' ' || (line[i] >= 9 && line[i] <= 13))
			i++;
		if (line[i])
			process_line(shell, line);
		free(line);
	}
}
