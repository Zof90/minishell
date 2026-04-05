/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schouite <schouite@student.42paris.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 16:40:14 by schouite          #+#    #+#             */
/*   Updated: 2025/11/21 15:38:46 by schouite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	*ft_memset(void *s, int c, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		((char *)s)[i] = (unsigned char)c;
		i++;
	}
	return (s);
}
/* #include<string.h>
#include <stdio.h>

int	main(void)
{
	int	str[5] ;
	int	i;

	i = 0;
	memset(str, 44, 2);
	while (i < 5)
	{
		printf("%d\n",str[i]);
		i++;
	}
} */
