/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_cleanup.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azaytsev <azaytsev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 09:29:21 by azaytsev          #+#    #+#             */
/*   Updated: 2026/04/28 09:34:28 by azaytsev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gc.h"
#include "minishell.h"

void	cleanup_shell(t_shell *shell)
{
	gc_free(shell);
	free_env(shell->env);
	shell->env = NULL;
	rl_clear_history();
}
