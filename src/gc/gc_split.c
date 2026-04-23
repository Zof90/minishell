/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zof <zof@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/21 17:28:47 by schouite          #+#    #+#             */
/*   Updated: 2026/04/23 17:35:36 by zof              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gc.h"
#include "minishell.h"

static int	ft_count_word(char const *s, char c)
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

char	**gc_split(t_shell *shell, char const *s, char c)
{
	char **ptr;
	int j;
	int start;
	int end;

	j = 0;
	start = 0;
	end = 0;
	ptr = gc_malloc(shell, sizeof(char *) * (ft_count_word(s, c) + 1));
	if (ptr == NULL)
		return (NULL);
	while (j < ft_count_word(s, c))
	{
		start = ft_satrt(s, end, c);
		end = ft_end(s, start, c);
		ptr[j] = gc_substr(shell, s, start, (end - start));
		if (!ptr[j])
			return (NULL);
		j++;
	}
	ptr[j] = NULL;
	return (ptr);
}