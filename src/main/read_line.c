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
		return (free(buf), NULL);
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

char	*read_line_fd(int fd)
{
	char	*buf;
	size_t	cap;
	size_t	len;
	char	c;
	ssize_t	n;

	cap = 64;
	buf = malloc(cap);
	if (!buf)
		return (NULL);
	len = 0;
	n = read(fd, &c, 1);
	while (n == 1)
	{
		if (c == '\n')
			return (buf[len] = '\0', buf);
		buf = push_char(buf, &cap, &len, c);
		if (!buf)
			return (NULL);
		n = read(fd, &c, 1);
	}
	if (n <= 0 && len == 0)
		return (free(buf), NULL);
	return (buf[len] = '\0', buf);
}
