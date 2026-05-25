/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_noargs.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azaytsev <azaytsev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/18 17:00:00 by azaytsev          #+#    #+#             */
/*   Updated: 2026/05/25 22:00:00 by azaytsev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	save_std(int *fd_in, int *fd_out)
{
	*fd_in = dup(0);
	if (*fd_in == -1)
		return (print_error("dup", strerror(errno)), -1);
	*fd_out = dup(1);
	if (*fd_out == -1)
	{
		close(*fd_in);
		return (print_error("dup", strerror(errno)), -1);
	}
	return (0);
}

static int	restore_std(int fd_in, int fd_out)
{
	int	ret;

	ret = 0;
	if (dup2(fd_in, 0) == -1)
	{
		print_error("dup2", strerror(errno));
		ret = -1;
	}
	if (dup2(fd_out, 1) == -1)
	{
		print_error("dup2", strerror(errno));
		ret = -1;
	}
	close(fd_in);
	close(fd_out);
	return (ret);
}

int	run_noargs(t_shell *shell, t_cmd *cmd)
{
	int		fd_in;
	int		fd_out;
	t_redir	*redir;
	int		ret;

	if (save_std(&fd_in, &fd_out) == -1)
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
	if (restore_std(fd_in, fd_out) == -1)
		ret = 1;
	shell->exit_status = ret;
	return (ret);
}
