/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schouite <schouite@student.42paris.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 18:31:47 by schouite          #+#    #+#             */
/*   Updated: 2025/11/23 11:40:13 by schouite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stddef.h>

size_t	ft_strlcat(char *dst, const char *src, size_t siz)
{
	size_t	i;
	size_t	j;
	size_t	l;

	i = 0;
	j = 0;
	l = 0;
	while (src[i])
		i++;
	while (dst[j])
		j++;
	if (siz <= j)
		return (i + siz);
	while (src[l] && j + l < siz - 1)
	{
		dst[j + l] = src[l];
		l++;
	}
	dst[j + l] = '\0';
	return (i + j);
}

/*  #include<stdio.h>
int	main(void)
{
	char	dst[12] = "salut";
	char	str[15] = "je suis zof";

	ft_strlcat(dst, str,17);
	printf("%s\n",dst);
} */
