/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schouite <schouite@student.42paris.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 11:18:32 by schouite          #+#    #+#             */
/*   Updated: 2025/11/21 15:40:24 by schouite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	ft_bzero(void *s, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		((char *)s)[i] = '\0';
		i++;
	}
}
/* #include<stdio.h>
#include <string.h>

int	main(void)
{
	char	s[] = "salut c'est zof";

	bzero(s, 6);
	printf("%c\n",s[6]);
}
 */
