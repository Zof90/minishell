/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_noargs.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azaytsev <azaytsev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/18 17:13:46 by azaytsev          #+#    #+#             */
/*   Updated: 2026/05/25 22:18:53 by azaytsev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	save_std(int *std)
{
	std[0] = dup(0);
	if (std[0] == -1)
		return (print_error("dup", strerror(errno)), -1);
	std[1] = dup(1);
	if (std[1] == -1)
	{
		close(std[0]);
		return (print_error("dup", strerror(errno)), -1);
	}
	std[2] = dup(2);
	if (std[2] == -1)
	{
		close(std[0]);
		close(std[1]);
		return (print_error("dup", strerror(errno)), -1);
	}
	return (0);
}

static int	restore_std(int *std, t_redir *redirs)
{
	int	ret;

	ret = 0;
	if (dup2(std[0], 0) == -1)
	{
		print_error("dup2", strerror(errno));
		ret = -1;
	}
	if (dup2(std[1], 1) == -1)
	{
		print_error("dup2", strerror(errno));
		ret = -1;
	}
	if (dup2(std[2], 2) == -1)
	{
		print_error("dup2", strerror(errno));
		ret = -1;
	}
	close(std[0]);
	close(std[1]);
	close(std[2]);
	reap_heredoc_writers(redirs);
	return (ret);
}

int	run_noargs(t_shell *shell, t_cmd *cmd)
{
	int		std[3];
	t_redir	*redir;
	int		ret;

	if (save_std(std) == -1)
	{
		shell->exit_status = 1;
		return (1);
	}
	redir = cmd->redirs;
	ret = 0;
	while (redir)
	{
		if (run_redir(redir, -1) == -1)
		{
			ret = 1;
			break ;
		}
		redir = redir->next;
	}
	if (restore_std(std, cmd->redirs) == -1)
		ret = 1;
	shell->exit_status = ret;
	return (ret);
}
