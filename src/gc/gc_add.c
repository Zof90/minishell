/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_add.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 15:03:35 by codespace         #+#    #+#             */
/*   Updated: 2026/04/20 15:15:50 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_gc	*gc_new(t_shell *shell, void *ptr)
{
	t_gc	*gc;

    gc = malloc(sizeof(ptr));
    if (!gc)
        return(NULL);
    
}
void	gc_add(t_shell *shell, void *ptr)
{
	void	*tmp;

	if (!shell->gc)
	{
		shell->gc = ptr;
		shell->gc->next = NULL;
	}
	tmp = shell->gc;
	shell->gc = shell->gc->next;
	shell->gc = tmp;
}
