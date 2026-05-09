/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zof <zof@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 14:41:36 by codespace         #+#    #+#             */
/*   Updated: 2026/05/09 17:53:01 by zof              ###   ########.fr       */
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
char	*gc_strjoin(t_shell *shell, char const *s1, char const *s2);
char	*gc_itoa(t_shell *shell, int n);
void	gc_free(t_shell *shell);
char	**gc_split(t_shell *shell, char const *s, char c);
#endif