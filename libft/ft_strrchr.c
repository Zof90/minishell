/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schouite <schouite@student.42paris.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/15 18:57:06 by schouite          #+#    #+#             */
/*   Updated: 2025/11/23 14:58:12 by schouite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	char	*str;

	i = 0;
	str = 0;
	while (s[i])
	{
		if (s[i] == (unsigned char)c)
			str = (char *)&s[i];
		i++;
	}
	if ((unsigned char)c == '\0')
		str = (char *)&s[i];
	return (str);
}
/* #include<stdio.h>
#include <string.h>

int	main(void)
{
	char	s[] = "je suis moi";
	int		c;
	char	*resultat;

	c = 'A';
	resultat = ft_strrchr(s, c);
	if (resultat)
		printf("%s\n",resultat);
	else
		printf("no occurence find\n");
} */
