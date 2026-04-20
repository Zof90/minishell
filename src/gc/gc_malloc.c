/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 14:15:25 by codespace         #+#    #+#             */
/*   Updated: 2026/04/20 15:03:18 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    *gc_malloc(t_shell *shell, size_t size)
{
    void    *ptr;

    ptr = malloc(size);
    if (!ptr)
        return(NULL);
    gc_add(shell, ptr);
    return(ptr);
}
