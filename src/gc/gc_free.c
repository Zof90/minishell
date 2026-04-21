/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schouite <schouite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/21 18:06:38 by schouite          #+#    #+#             */
/*   Updated: 2026/04/21 18:17:15 by schouite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	gc_free(t_gc *gc)
{
	t_gc	*current;

	if (!gc)
		return ;
	current = gc;
	while (current)
	{
		current = current->next;
		free(gc);
		gc = current;
	}
}
