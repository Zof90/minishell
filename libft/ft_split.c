/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schouite <schouite@student.42paris.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 16:12:32 by schouite          #+#    #+#             */
/*   Updated: 2025/11/23 11:41:37 by schouite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

int	ft_count_word(char const *s, char c)
{
	int	i;
	int	nb_word;
	int	in_word;

	i = 0;
	nb_word = 0;
	in_word = 0;
	while (s[i])
	{
		if (s[i] != c && !in_word)
		{
			nb_word++;
			in_word = 1;
		}
		else if (s[i] == c)
		{
			in_word = 0;
		}
		i++;
	}
	return (nb_word);
}

static int	ft_satrt(char const *s, int end, char c)
{
	int	i;

	i = 0;
	while (s[i + end] && s[i + end] == c)
		i++;
	return (i + end);
}

static int	ft_end(char const *s, int start, char c)
{
	int	i;

	i = 0;
	while (s[i + start] && s[i + start] != c)
		i++;
	return (i + start);
}

void	ft_free(char **s, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		free(s[i]);
		i++;
	}
	free(s);
}

char	**ft_split(char const *s, char c)
{
	char	**ptr;
	int		j;
	int		start;
	int		end;

	j = 0;
	start = 0;
	end = 0;
	ptr = malloc(sizeof(char *) * (ft_count_word(s, c) + 1));
	if (ptr == NULL)
		return (NULL);
	while (j < ft_count_word(s, c))
	{
		start = ft_satrt(s, end, c);
		end = ft_end(s, start, c);
		ptr[j] = ft_substr(s, start, (end - start));
		if (ptr[j] == NULL)
		{
			ft_free(ptr, j);
			return (NULL);
		}
		j++;
	}
	ptr[j] = NULL;
	return (ptr);
}
/* #include <stdio.h>

int	main(void)
{
	int		i;
	char	s[50] = "      split       this for   me  !       ";
	char	**ptr;
	char	c;

	i = 0;
	c = ' ';
	ptr = ft_split(s, c);
	while (i < ft_count_word(s, c))
	{
		printf("%s", ptr[i]);
		i++;
	}
	ft_free(ptr, ft_count_word(s, c));
} */
