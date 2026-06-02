/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_msg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azaytsev <azaytsev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/02 09:14:33 by azaytsev          #+#    #+#             */
/*   Updated: 2026/06/02 09:48:51 by azaytsev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_error_parts(const char **parts)
{
	size_t	len;
	size_t	pos;
	size_t	n;
	int		i;
	char	*line;

	len = 0;
	i = 0;
	while (parts[i])
		len += ft_strlen(parts[i++]);
	line = malloc(len + 1);
	if (!line)
		return ;
	pos = 0;
	i = 0;
	while (parts[i])
	{
		n = ft_strlen(parts[i]);
		ft_memcpy(line + pos, parts[i], n);
		pos += n;
		i++;
	}
	write(2, line, pos);
	free(line);
}
