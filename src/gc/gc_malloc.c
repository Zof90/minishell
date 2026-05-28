/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schouite <schouite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 14:15:25 by schouite          #+#    #+#             */
/*   Updated: 2026/04/29 15:39:17 by schouite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gc.h"
#include "minishell.h"

static t_gc	*gc_new(void *ptr)
{
	t_gc	*gc;

	gc = malloc(sizeof(t_gc));
	if (!gc)
		return (NULL);
	gc->ptr = ptr;
	gc->next = NULL;
	return (gc);
}

static bool	gc_add(t_shell *shell, void *ptr)
{
	t_gc	*new;

	if (!ptr)
		return (false);
	new = gc_new(ptr);
	if (!new)
		return (false);
	new->next = shell->gc;
	shell->gc = new;
	return (true);
}

void	*gc_malloc(t_shell *shell, size_t size)
{
	void	*ptr;

	ptr = malloc(size);
	if (!ptr)
		return (NULL);
	if (!gc_add(shell, ptr))
	{
		free(ptr);
		return (NULL);
	}
	return (ptr);
}
