/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_noargs.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azaytsev <azaytsev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/18 17:00:00 by azaytsev          #+#    #+#             */
/*   Updated: 2026/05/18 17:00:00 by azaytsev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	run_noargs(t_shell *shell, t_cmd *cmd)
{
	int		fd_in;
	int		fd_out;
	t_redir	*redir;
	int		ret;

	fd_in = dup(0);
	fd_out = dup(1);
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
	dup2(fd_in, 0);
	dup2(fd_out, 1);
	close(fd_in);
	close(fd_out);
	shell->exit_status = ret;
	return (ret);
}
