/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schouite <schouite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/21 18:06:38 by schouite          #+#    #+#             */
/*   Updated: 2026/04/21 18:34:37 by schouite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
