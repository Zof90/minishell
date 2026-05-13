/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azaytsev <azaytsev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/13 09:00:00 by azaytsev          #+#    #+#             */
/*   Updated: 2026/05/13 09:00:00 by azaytsev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gc.h"
#include "minishell.h"

static int	skip_quoted_len(const char *str, int *i)
{
	int		len;
	char	quote;

	len = 0;
	quote = str[(*i)++];
	while (str[*i] && str[*i] != quote)
	{
		len++;
		(*i)++;
	}
	if (str[*i])
		(*i)++;
	return (len);
}

static int	stripped_len(const char *str)
{
	int	len;
	int	i;

	len = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '"')
			len += skip_quoted_len(str, &i);
		else
		{
			len++;
			i++;
		}
	}
	return (len);
}

static void	copy_quoted(const char *str, int *i, char *result, int *j)
{
	char	quote;

	quote = str[(*i)++];
	while (str[*i] && str[*i] != quote)
		result[(*j)++] = str[(*i)++];
	if (str[*i])
		(*i)++;
}

char	*strip_quotes(t_shell *shell, const char *str)
{
	char	*result;
	int		i;
	int		j;

	result = gc_malloc(shell, stripped_len(str) + 1);
	if (!result)
		return (NULL);
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '"')
			copy_quoted(str, &i, result, &j);
		else
			result[j++] = str[i++];
	}
	result[j] = '\0';
	return (result);
}
