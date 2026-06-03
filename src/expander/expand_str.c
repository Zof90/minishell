/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_str.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azaytsev <azaytsev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/13 09:17:03 by azaytsev          #+#    #+#             */
/*   Updated: 2026/05/24 15:22:10 by azaytsev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gc.h"
#include "minishell.h"

static int	escapes_in_dquote(char c)
{
	return (c == '\\' || c == '"' || c == '$' || c == '`' || c == '\n');
}

static char	*expand_backslash(t_shell *sh, const char *str, int *i,
		int in_double)
{
	char	c;

	c = str[*i + 1];
	if (!c)
	{
		(*i)++;
		return (emit_char(sh, '\\', 1));
	}
	if (in_double && !escapes_in_dquote(c))
	{
		(*i)++;
		return (emit_char(sh, '\\', 1));
	}
	*i += 2;
	return (emit_char(sh, c, 1));
}

static int	is_expandable_dollar(const char *str, int i, t_quotes *q)
{
	if (q->in_single)
		return (0);
	if (str[i] != '$')
		return (0);
	if (!str[i + 1] || str[i + 1] == ' ' || str[i + 1] == '\t')
		return (0);
	if (q->in_double && (str[i + 1] == '"' || str[i + 1] == '\''))
		return (0);
	return (1);
}

static char	*expand_char(const char *str, int *i, t_quotes *q, t_shell *sh)
{
	char	*val;

	if (str[*i] == '\'' && !q->in_double)
	{
		q->in_single = !q->in_single;
		(*i)++;
		return (gc_strdup(sh, ""));
	}
	if (str[*i] == '"' && !q->in_single)
	{
		q->in_double = !q->in_double;
		(*i)++;
		return (gc_strdup(sh, ""));
	}
	if (str[*i] == '\\' && !q->in_single)
		return (expand_backslash(sh, str, i, q->in_double));
	if (is_expandable_dollar(str, *i, q))
	{
		val = resolve_dollar(str, i, sh);
		if (q->in_double)
			return (protect_whitespace(sh, val));
		return (val);
	}
	return (emit_char(sh, str[(*i)++], q->in_single || q->in_double));
}

char	*expand_str(const char *str, t_shell *shell)
{
	t_strbuf	buf;
	t_quotes	quotes;
	int			i;

	if (strbuf_init(&buf))
		return (NULL);
	i = 0;
	quotes.in_single = 0;
	quotes.in_double = 0;
	while (str[i])
	{
		if (strbuf_append(&buf, expand_char(str, &i, &quotes, shell)))
			return (NULL);
	}
	return (strbuf_finish(shell, &buf));
}
