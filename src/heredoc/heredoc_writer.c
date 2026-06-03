/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_writer.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azaytsev <azaytsev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/02 16:36:44 by azaytsev          #+#    #+#             */
/*   Updated: 2026/06/02 16:36:47 by azaytsev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gc.h"
#include "minishell.h"

static void	close_inherited_fds(int keep)
{
	int	fd;

	fd = 3;
	while (fd < 1024)
	{
		if (fd != keep)
			close(fd);
		fd++;
	}
}

static void	heredoc_writer_child(t_redir *redir, int pfd[2])
{
	size_t	len;

	signal(SIGPIPE, SIG_IGN);
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	close_inherited_fds(pfd[1]);
	len = ft_strlen(redir->heredoc_content);
	write(pfd[1], redir->heredoc_content, len);
	close(pfd[1]);
	exit(0);
}

int	spawn_heredoc_writer(t_redir *redir, int pfd[2])
{
	pid_t	pid;

	if (!redir->heredoc_content || !*redir->heredoc_content)
		return (0);
	pid = fork();
	if (pid == -1)
	{
		print_error("heredoc", strerror(errno));
		return (-1);
	}
	if (pid == 0)
		heredoc_writer_child(redir, pfd);
	redir->heredoc_pid = pid;
	return (0);
}

void	reap_heredoc_writers(t_redir *redirs)
{
	while (redirs)
	{
		if (redirs->heredoc_pid > 0)
		{
			waitpid(redirs->heredoc_pid, NULL, 0);
			redirs->heredoc_pid = -1;
		}
		redirs = redirs->next;
	}
}
