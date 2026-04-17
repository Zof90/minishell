/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schouite <schouite@student.42paris.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/16 20:41:51 by schouite          #+#    #+#             */
/*   Updated: 2025/11/22 22:50:24 by schouite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strdup(const char *s)
{
	char	*str;

	str = malloc(ft_strlen(s) + 1);
	if (!str)
		return (NULL);
	ft_memcpy(str, s, ft_strlen(s));
	str[ft_strlen(s)] = '\0';
	return (str);
}
/* #include <stdio.h>
#include <string.h>

int	main(void)
{
	char	s[] = "je suis zof";

	printf("%s\n", ft_strdup(s));
	printf("%d\n", ft_memcmp(s, ft_strdup(s), (ft_strlen(s))));
} */
