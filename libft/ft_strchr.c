/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schouite <schouite@student.42paris.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/15 18:03:28 by schouite          #+#    #+#             */
/*   Updated: 2025/11/23 12:09:47 by schouite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	size_t	i;
	char	*str;

	i = 0;
	str = (char *)s;
	while (*str)
	{
		if (s[i] == (char)c)
			return (str);
		str++;
		i++;
	}
	if ((char)c == '\0')
		return (str);
	return (NULL);
}
/* #include<stdio.h>
#include <string.h>

int	main(void)
{

	char	s[] = "je suis moi";
	int	c;
	char	*resultat;

	c = 'M';
	resultat = ft_strchr(s, c);
	if (resultat)
		printf("%s\n",resultat);
	else
		printf("no occurence find\n");
} */
