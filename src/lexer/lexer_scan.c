/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_scan.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zof <zof@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/23 10:17:55 by zof               #+#    #+#             */
/*   Updated: 2026/04/23 13:15:12 by zof              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	in_quotes_size(char str, char c, int *i)
{
	while (str[i++])
	{
		if (str[i] == c)
			return (i);
	}
	return (-1);
}
int	token_size(char *str)
{
	int	i;

	i = 0;
	while ((str[i] == ' ') || (str[i] >= 9 && str[i] <= 13))
		i++;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			if (!in_quotes_size(str, str[i], &i))
				return (-1);
		}
		if (str[i] == ' ')
			return (i);
		else if (!(str[i] != '>' && str[i] != '<' && str[i] != '>>'
				&& str[i] != '<<' && str[i] != '|'))
                return(i++);
			i++;
	}
	return (i);
}
