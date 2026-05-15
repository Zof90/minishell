/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_utile2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azaytsev <azaytsev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/13 09:00:00 by azaytsev          #+#    #+#             */
/*   Updated: 2026/05/13 09:00:00 by azaytsev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gc.h"
#include "minishell.h"

char	*gc_strjoin(t_shell *shell, char const *s1, char const *s2)
{
	size_t	len1;
	size_t	len2;
	char	*str;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (gc_strdup(shell, s2));
	if (!s2)
		return (gc_strdup(shell, s1));
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	str = gc_malloc(shell, len1 + len2 + 1);
	if (!str)
		return (NULL);
	ft_memcpy(str, s1, len1);
	ft_memcpy(str + len1, s2, len2);
	str[len1 + len2] = '\0';
	return (str);
}

static int	itoa_len(long nb)
{
	int	i;

	i = 0;
	if (nb <= 0)
		i = 1;
	while (nb)
	{
		nb /= 10;
		i++;
	}
	return (i);
}

char	*gc_itoa(t_shell *shell, int n)
{
	long	nb;
	int		len;
	char	*str;

	nb = n;
	len = itoa_len(nb);
	str = gc_malloc(shell, len + 1);
	if (!str)
		return (NULL);
	str[len] = '\0';
	if (nb == 0)
		str[0] = '0';
	if (nb < 0)
	{
		str[0] = '-';
		nb = -nb;
	}
	while (nb > 0)
	{
		str[--len] = nb % 10 + '0';
		nb /= 10;
	}
	return (str);
}
