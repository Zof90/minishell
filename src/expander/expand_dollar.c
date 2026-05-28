/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_dollar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azaytsev <azaytsev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/13 09:00:00 by azaytsev          #+#    #+#             */
/*   Updated: 2026/05/13 09:00:00 by azaytsev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gc.h"
#include "minishell.h"

char	*char_to_str(t_shell *shell, char c)
{
	char	*str;

	str = gc_malloc(shell, 2);
	if (!str)
		return (NULL);
	str[0] = c;
	str[1] = '\0';
	return (str);
}

char	*emit_one(t_shell *sh, char c, int nosplit)
{
	if (nosplit && (c == ' ' || (c >= 9 && c <= 13)))
		c = 1;
	return (char_to_str(sh, c));
}

char	*escape_ws(t_shell *shell, const char *src)
{
	char	*r;
	int		i;

	if (!src)
		return (NULL);
	r = gc_malloc(shell, ft_strlen(src) + 1);
	if (!r)
		return (NULL);
	i = 0;
	while (src[i])
	{
		if (src[i] == ' ' || (src[i] >= 9 && src[i] <= 13))
			r[i] = 1;
		else
			r[i] = src[i];
		i++;
	}
	r[i] = '\0';
	return (r);
}

static char	*extract_var_name(t_shell *shell, const char *str, int *i)
{
	int	start;

	start = *i;
	while (str[*i] && (ft_isalnum(str[*i]) || str[*i] == '_'))
		(*i)++;
	if (*i == start)
		return (NULL);
	return (gc_substr(shell, str, start, *i - start));
}

char	*resolve_dollar(const char *str, int *i, t_shell *shell)
{
	char	*name;
	char	*val;

	(*i)++;
	if (str[*i] == '?')
	{
		(*i)++;
		return (gc_itoa(shell, shell->exit_status));
	}
	if (str[*i] == '\'' || str[*i] == '"')
		return (gc_strdup(shell, ""));
	if (ft_isdigit(str[*i]))
	{
		(*i)++;
		return (gc_strdup(shell, ""));
	}
	if (!str[*i] || (!ft_isalpha(str[*i]) && str[*i] != '_'))
		return (gc_strdup(shell, "$"));
	name = extract_var_name(shell, str, i);
	if (!name)
		return (gc_strdup(shell, "$"));
	val = env_get(shell->env, name);
	if (val)
		return (gc_strdup(shell, val));
	return (gc_strdup(shell, ""));
}
