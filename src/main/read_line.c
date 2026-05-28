/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azaytsev <azaytsev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/18 17:00:00 by azaytsev          #+#    #+#             */
/*   Updated: 2026/05/19 10:00:00 by azaytsev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*grow_buf(char *buf, size_t len, size_t new_cap)
{
	char	*new_buf;

	new_buf = malloc(new_cap);
	if (!new_buf)
	{
		free(buf);
		return (NULL);
	}
	if (buf)
	{
		ft_memcpy(new_buf, buf, len);
		free(buf);
	}
	return (new_buf);
}

static char	*push_char(char *buf, size_t *cap, size_t *len, char c)
{
	if (*len + 1 >= *cap)
	{
		*cap *= 2;
		buf = grow_buf(buf, *len, *cap);
		if (!buf)
			return (NULL);
	}
	buf[(*len)++] = c;
	return (buf);
}

static char	*finish_line(char *buf, size_t len)
{
	buf[len] = '\0';
	return (buf);
}

static char	*init_line_buf(size_t *cap, size_t *len)
{
	*cap = 64;
	*len = 0;
	return (malloc(*cap));
}

char	*read_line_fd(int fd)
{
	char	*buf;
	size_t	cap;
	size_t	len;
	char	c;
	ssize_t	n;

	buf = init_line_buf(&cap, &len);
	if (!buf)
		return (NULL);
	n = read(fd, &c, 1);
	while (n == 1)
	{
		if (c == '\n')
			return (finish_line(buf, len));
		buf = push_char(buf, &cap, &len, c);
		if (!buf)
			return (NULL);
		n = read(fd, &c, 1);
	}
	if (n <= 0 && len == 0)
	{
		free(buf);
		return (NULL);
	}
	return (finish_line(buf, len));
}
