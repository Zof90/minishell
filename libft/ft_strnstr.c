/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schouite <schouite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/16 18:45:00 by schouite          #+#    #+#             */
/*   Updated: 2025/11/22 22:16:14 by schouite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (!little[i])
		return ((char *)big);
	while (((char *)big)[i] && i < len)
	{
		j = 0;
		while (little[j] && ((char *)big)[i + j] == little[j] && i + j < len)
		{
			if (!little[j + 1])
				return (((char *)big + i));
			j++;
		}
		i++;
	}
	return (0);
}
