/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_loop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schouite <schouite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 09:27:42 by azaytsev          #+#    #+#             */
/*   Updated: 2026/06/03 17:57:51 by schouite         ###   ########.fr       */
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
	{
		shell->exit_status = 2;
		if (!isatty(STDIN_FILENO))
			shell->running = 0;
		return (0);
	}
	if (syntax_check(token))
	{
		shell->exit_status = 2;
		if (!isatty(STDIN_FILENO))
			shell->running = 0;
		return (0);
	}
	*out = parse(shell, token);
	if (*out)
		*out = expand(*out, shell);
	if (*out && collect_heredocs(*out, shell))
	{
		shell->exit_status = 130;
		return (0);
	}
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

	shell->interactive = isatty(STDIN_FILENO);
	if (shell->interactive)
		tcgetattr(STDIN_FILENO, &shell->original_term);
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
