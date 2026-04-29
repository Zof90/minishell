/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zof <zof@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 14:41:36 by codespace         #+#    #+#             */
/*   Updated: 2026/04/27 14:43:14 by zof              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GC_H
# define GC_H
# include "minishell.h"
# include <stddef.h>

void	*gc_calloc(t_shell *shell, size_t nmemb, size_t size);
void	*gc_malloc(t_shell *shell, size_t size);
char	*gc_substr(t_shell *shell, char const *s, unsigned int start,
			size_t len);
char	*gc_strdup(t_shell *shell, const char *s);
void	gc_free(t_shell *shell);
#endif