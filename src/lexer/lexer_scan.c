/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_scan.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zof <zof@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/23 10:17:55 by zof               #+#    #+#             */
/*   Updated: 2026/04/23 16:58:56 by zof              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	in_quotes_size(char *str, char c, int *len)
{
	while (*str)
	{
		if (*str == c)
			return (len);
		str++;
		len++;
	}
	return (-1);
}
int	token_size(char *str)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while ((str[i] == ' ') || (str[i] >= 9 && str[i] <= 13))
		i++;
	while (str[i])
	{
		if (!(str[i] != '>' && str[i] != '<' && str[i] != '>>' && str[i] != '<<'
				&& str[i] != '|'))
			return (++len);
		else if (str[i] == '\'' || str[i] == '\"')
		{
			if (!in_quotes_size(&str[i], str[i], &len))
				return (-1);
		}
		if (str[i] == ' ')
			break ;
		i = i + ++len;
	}
	return (len);
}
