/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schouite <schouite@student.42paris.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/15 20:30:01 by schouite          #+#    #+#             */
/*   Updated: 2025/11/22 21:21:12 by schouite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*str;

	i = 0;
	while (i < n)
	{
		if (((unsigned char *)s)[i] == (unsigned char)c)
		{
			str = &((unsigned char *)s)[i];
			return (str);
		}
		i++;
	}
	return (0);
}
/* #include<stdio.h>
#include <string.h>

int	main(void)
{
	char	s[] = "je suis moi";
	char	c;

	c = 's';
	printf("%s\n",(char *) ft_memchr(s, c, 4));
} */
