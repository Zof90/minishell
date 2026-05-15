/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_str.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azaytsev <azaytsev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/13 09:00:00 by azaytsev          #+#    #+#             */
/*   Updated: 2026/05/13 09:00:00 by azaytsev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gc.h"
#include "minishell.h"

static int	is_expandable_dollar(const char *str, int i, int in_sq)
{
	if (in_sq)
		return (0);
	if (str[i] != '$')
		return (0);
	if (!str[i + 1] || str[i + 1] == ' ' || str[i + 1] == '\t')
		return (0);
	return (1);
}

static char	*handle_char(const char *str, int *i, int *quotes, t_shell *sh)
{
	if (str[*i] == '\'' && !quotes[1])
	{
		quotes[0] = !quotes[0];
		return (char_to_str(sh, str[(*i)++]));
	}
	if (str[*i] == '"' && !quotes[0])
	{
		quotes[1] = !quotes[1];
		return (char_to_str(sh, str[(*i)++]));
	}
	if (is_expandable_dollar(str, *i, quotes[0]))
		return (resolve_dollar(str, i, sh));
	return (char_to_str(sh, str[(*i)++]));
}

char	*expand_str(const char *str, t_shell *shell)
{
	char	*result;
	char	*piece;
	int		i;
	int		quotes[2];

	result = NULL;
	i = 0;
	quotes[0] = 0;
	quotes[1] = 0;
	while (str[i])
	{
		piece = handle_char(str, &i, quotes, shell);
		if (!piece)
			return (NULL);
		result = gc_strjoin(shell, result, piece);
		if (!result)
			return (NULL);
	}
	if (!result)
		return (gc_strdup(shell, ""));
	return (result);
}
