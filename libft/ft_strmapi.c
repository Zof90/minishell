/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schouite <schouite@student.42paris.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 12:13:51 by schouite          #+#    #+#             */
/*   Updated: 2025/11/21 15:34:26 by schouite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
//char	ft_modification(unsigned int i, char c);

int	ft_len(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		i++;
	}
	return (i);
}

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned char	i;
	char			*str;
	int				len;

	i = 0;
	len = ft_len(s);
	str = (char *)malloc(sizeof(char) * len + 1);
	if (!str)
		return (NULL);
	while (s[i])
	{
		str[i] = f(i, s[i]);
		i++;
	}
	str[i] = '\0';
	return (str);
}
/* #include <stdio.h>

static char	ft_modification(unsigned int i, char c)
{
	char	res;

	res = i + c;
	return (res);
}

int	main(void)
{
	char	s[] = "hola";

	printf("%s\n", ft_strmapi(s, ft_modification));
} */
