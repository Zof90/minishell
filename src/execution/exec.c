/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zof <zof@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/09 15:33:25 by zof               #+#    #+#             */
/*   Updated: 2026/05/09 18:56:26 by zof              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gc.h"
#include "minishell.h"

static pid_t	*init_var(t_shell *shell, int *len, pid_t *pid, t_cmd *cmd)
{
	*len = calculate_len(cmd->args);
	pid = gc_malloc(shell, *len * sizeof(pid_t));
	if (!pid)
		return (NULL);
	return (pid);
}

bool	run_executor(t_shell *shell, t_cmd *cmd)
{
	int i;
	int pfd[2];
    t_cmd *current;
    
    current = cmd;
    current->pid = fork();
    
    if (!pid)
        return(NULL);
	while (cmd)
	{
	}
}