/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zof <zof@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 14:15:25 by codespace         #+#    #+#             */
/*   Updated: 2026/04/23 17:46:55 by zof              ###   ########.fr       */
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
	t_gc	*tmp;

	new = gc_new(ptr);
	if (!new)
		return (false);
	if (!ptr)
		return (false);
	if (!shell->gc)
	{
		shell->gc = new;
		return (true);
	}
	tmp = shell->gc;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	return (true);
}

void	*gc_malloc(t_shell *shell, size_t size)
{
	void	*ptr;

	ptr = malloc(size);
	if (!ptr)
		return (NULL);
	if (!gc_add(shell, ptr))
		return (NULL);
	return (ptr);
}
