/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schouite <schouite@student.42paris.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 12:57:06 by schouite          #+#    #+#             */
/*   Updated: 2025/11/23 11:35:10 by schouite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char *))
{
	int	i;

	i = 0;
	while (s[i])
	{
		f(i, &s[i]);
		i++;
	}
}
/* #include <stdio.h>

static void	ft_modification(unsigned int i, char *s)
{
	s[i] += 1;
}

int	main(void)
{
	char	s[] = "hola";

	ft_striteri(s, ft_modification);
	printf("%s\n", s);
} */
