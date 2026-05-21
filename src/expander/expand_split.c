/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_split.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azaytsev <azaytsev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/21 09:00:00 by azaytsev          #+#    #+#             */
/*   Updated: 2026/05/21 09:00:00 by azaytsev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gc.h"
#include "minishell.h"

int	field_has_quotes(const char *str)
{
	while (*str)
	{
		if (*str == '\'' || *str == '"')
			return (1);
		str++;
	}
	return (0);
}

int	field_count_words(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
			i++;
		if (str[i])
			count++;
		while (str[i] && !(str[i] == ' ' || (str[i] >= 9 && str[i] <= 13)))
			i++;
	}
	return (count);
}

int	field_append_words(t_shell *shell, char **args, int *j, char *str)
{
	int	i;
	int	start;

	i = 0;
	while (str[i])
	{
		while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
			i++;
		start = i;
		while (str[i] && !(str[i] == ' ' || (str[i] >= 9 && str[i] <= 13)))
			i++;
		if (i > start)
		{
			args[*j] = gc_substr(shell, str, start, i - start);
			if (!args[*j])
				return (1);
			(*j)++;
		}
	}
	return (0);
}
