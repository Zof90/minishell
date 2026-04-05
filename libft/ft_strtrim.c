/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schouite <schouite@student.42paris.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 18:05:04 by schouite          #+#    #+#             */
/*   Updated: 2025/11/18 16:19:13 by schouite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static int	ft_start(char const *s1, char const *set)
{
	int	i;
	int	j;
	int	trigger;

	i = 0;
	trigger = 0;
	while (s1[i])
	{
		j = 0;
		while (set[j])
		{
			if (s1[i] == set[j])
				trigger = 1;
			j++;
		}
		if (!trigger)
			return (i);
		trigger = 0;
		i++;
	}
	return (0);
}

static int	ft_end(char const *s1, char const *set)
{
	int	i;
	int	j;
	int	trigger;

	trigger = 0;
	i = ft_strlen(s1) - 1;
	while (i >= 0)
	{
		j = 0;
		while (set[j])
		{
			if (s1[i] == set[j])
				trigger = 1;
			j++;
		}
		if (!trigger)
			return (i + 1);
		trigger = 0;
		i--;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*ptr;
	int		len;

	len = ft_end(s1, set) - ft_start(s1, set);
	ptr = ft_substr(s1, ft_start(s1, set), len);
	return (ptr);
}
/* #include <stdio.h>

int	main(void)
{
	char	s1[] = "je/jjjjjjje suis moi     j       /";
	char	set[] = "j i/";

	printf("%s\n", ft_strtrim(s1, set));
} */
