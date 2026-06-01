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

static int	is_dquote_escape(char c)
{
	return (c == '\\' || c == '"' || c == '$' || c == '`' || c == '\n');
}

static char	*append_escaped(t_shell *sh, const char *str, int *i, int dq)
{
	char	c;

	c = str[*i + 1];
	if (!c)
	{
		(*i)++;
		return (emit_one(sh, '\\', 1));
	}
	if (dq && !is_dquote_escape(c))
	{
		(*i)++;
		return (emit_one(sh, '\\', 1));
	}
	*i += 2;
	return (emit_one(sh, c, 1));
}

static int	is_expandable_dollar(const char *str, int i, int sq, int dq)
{
	if (sq)
		return (0);
	if (str[i] != '$')
		return (0);
	if (!str[i + 1] || str[i + 1] == ' ' || str[i + 1] == '\t')
		return (0);
	if (dq && (str[i + 1] == '"' || str[i + 1] == '\''))
		return (0);
	return (1);
}

static char	*handle_char(const char *str, int *i, int *q, t_shell *sh)
{
	char	*v;

	if (str[*i] == '\'' && !q[1])
	{
		q[0] = !q[0];
		(*i)++;
		return (gc_strdup(sh, ""));
	}
	if (str[*i] == '"' && !q[0])
	{
		q[1] = !q[1];
		(*i)++;
		return (gc_strdup(sh, ""));
	}
	if (str[*i] == '\\' && !q[0])
		return (append_escaped(sh, str, i, q[1]));
	if (is_expandable_dollar(str, *i, q[0], q[1]))
	{
		v = resolve_dollar(str, i, sh);
		if (q[1])
			return (escape_ws(sh, v));
		return (v);
	}
	return (emit_one(sh, str[(*i)++], q[0] || q[1]));
}

char	*expand_str(const char *str, t_shell *shell)
{
	t_xbuf	b;
	int		i;
	int		quotes[2];

	if (xbuf_init(&b))
		return (NULL);
	i = 0;
	quotes[0] = 0;
	quotes[1] = 0;
	while (str[i])
	{
		if (xbuf_append(&b, handle_char(str, &i, quotes, shell)))
			return (NULL);
	}
	return (xbuf_finish(shell, &b));
}
