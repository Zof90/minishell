/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schouite <schouite@student.42paris.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 12:38:48 by schouite          #+#    #+#             */
/*   Updated: 2025/11/23 16:52:48 by schouite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stddef.h>

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t	i;

	i = 0;
	if (!dest && !src)
		return (NULL);
	if ((size_t)src == (size_t)dest)
		return (dest);
	if ((size_t)src > (size_t)dest)
	{
		while (i < n)
		{
			((unsigned char *)dest)[i] = ((unsigned char *)src)[i];
			i++;
		}
	}
	else
	{
		while (n > 0)
		{
			n--;
			((unsigned char *)dest)[n] = ((unsigned char *)src)[n];
		}
	}
	return (dest);
}
/* #include <stdio.h>
#include <string.h>

int	main(void)
{
	char	buffer[11] = "je suis moi";
	char	*s;
	char	*dest;

	s = buffer;
	dest = buffer + 4;
	ft_memmove(dest, s, 11);
	printf("%s\n", dest);
} */
