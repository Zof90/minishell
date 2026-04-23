/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zof <zof@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/21 18:06:38 by schouite          #+#    #+#             */
/*   Updated: 2026/04/23 17:35:41 by zof              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gc.h"
#include <minishell.h>

void	gc_free(t_shell *shell)
{
	t_gc	*current;

	if (!shell->gc)
		return ;
	current = shell->gc;
	while (current)
	{
		current = current->next;
		free(shell->gc);
		shell->gc = current;
	}
	shell->gc = NULL;
}
