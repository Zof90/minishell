/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_buf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azaytsev <azaytsev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/31 16:31:47 by azaytsev          #+#    #+#             */
/*   Updated: 2026/05/31 16:42:09 by azaytsev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gc.h"
#include "minishell.h"

int	strbuf_init(t_strbuf *sb)
{
	sb->cap = 64;
	sb->len = 0;
	sb->buf = malloc(sb->cap);
	if (!sb->buf)
		return (1);
	return (0);
}

static int	strbuf_grow(t_strbuf *sb, size_t need)
{
	char	*new_data;
	size_t	new_cap;

	new_cap = sb->cap;
	while (sb->len + need + 1 > new_cap)
		new_cap *= 2;
	new_data = malloc(new_cap);
	if (!new_data)
	{
		free(sb->buf);
		sb->buf = NULL;
		return (1);
	}
	ft_memcpy(new_data, sb->buf, sb->len);
	free(sb->buf);
	sb->buf = new_data;
	sb->cap = new_cap;
	return (0);
}

int	strbuf_append(t_strbuf *sb, const char *str)
{
	size_t	add_len;

	if (!sb->buf)
		return (1);
	if (!str)
	{
		free(sb->buf);
		sb->buf = NULL;
		return (1);
	}
	add_len = ft_strlen(str);
	if (sb->len + add_len + 1 > sb->cap && strbuf_grow(sb, add_len))
		return (1);
	ft_memcpy(sb->buf + sb->len, str, add_len);
	sb->len += add_len;
	return (0);
}

char	*strbuf_finish(t_shell *sh, t_strbuf *sb)
{
	char	*out;

	if (!sb->buf)
		return (NULL);
	sb->buf[sb->len] = '\0';
	out = gc_strdup(sh, sb->buf);
	free(sb->buf);
	sb->buf = NULL;
	return (out);
}
