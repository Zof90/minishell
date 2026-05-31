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

int	xbuf_init(t_xbuf *b)
{
	b->cap = 64;
	b->len = 0;
	b->buf = malloc(b->cap);
	if (!b->buf)
		return (1);
	return (0);
}

static int	xbuf_grow(t_xbuf *b, size_t need)
{
	char	*nb;
	size_t	ncap;

	ncap = b->cap;
	while (b->len + need + 1 > ncap)
		ncap *= 2;
	nb = malloc(ncap);
	if (!nb)
	{
		free(b->buf);
		b->buf = NULL;
		return (1);
	}
	ft_memcpy(nb, b->buf, b->len);
	free(b->buf);
	b->buf = nb;
	b->cap = ncap;
	return (0);
}

int	xbuf_append(t_xbuf *b, const char *s)
{
	size_t	slen;

	if (!b->buf)
		return (1);
	if (!s)
	{
		free(b->buf);
		b->buf = NULL;
		return (1);
	}
	slen = ft_strlen(s);
	if (b->len + slen + 1 > b->cap && xbuf_grow(b, slen))
		return (1);
	ft_memcpy(b->buf + b->len, s, slen);
	b->len += slen;
	return (0);
}

char	*xbuf_finish(t_shell *sh, t_xbuf *b)
{
	char	*out;

	if (!b->buf)
		return (NULL);
	b->buf[b->len] = '\0';
	out = gc_strdup(sh, b->buf);
	free(b->buf);
	b->buf = NULL;
	return (out);
}
