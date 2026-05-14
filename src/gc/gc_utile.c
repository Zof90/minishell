/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_utile.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zof <zof@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/21 17:22:10 by schouite          #+#    #+#             */
/*   Updated: 2026/04/23 17:35:33 by zof              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gc.h"
#include "minishell.h"

void	*gc_calloc(t_shell *shell, size_t nmemb, size_t size)
{
	void	*ptr;

	if (nmemb != 0 && size > (size_t)-1 / nmemb)
		return (NULL);
	ptr = gc_malloc(shell, nmemb * size);
	if (!ptr)
		return (NULL);
	ft_memset(ptr, 0, nmemb * size);
	return (ptr);
}

char	*gc_strdup(t_shell *shell, const char *s)
{
	char	*str;

	str = gc_malloc(shell, ft_strlen(s) + 1);
	if (!str)
		return (NULL);
	ft_memcpy(str, s, ft_strlen(s));
	str[ft_strlen(s)] = '\0';
	return (str);
}

char	*gc_substr(t_shell *shell, char const *s, unsigned int start,
		size_t len)
{
	char	*str;

	if (!s)
		return (NULL);
	if (ft_strlen(s) <= start)
		return (gc_strdup(shell, ""));
	if (ft_strlen(s) - start < len)
		len = ft_strlen(s) - start;
	str = gc_malloc(shell, len + 1);
	if (!str)
		return (NULL);
	str = ft_memcpy(str, s + start, len);
	str[len] = '\0';
	return (str);
}
