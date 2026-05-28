/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_expand.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azaytsev <azaytsev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/24 15:30:00 by azaytsev          #+#    #+#             */
/*   Updated: 2026/05/24 15:30:00 by azaytsev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gc.h"
#include "minishell.h"

char	*read_hd_line(void)
{
	if (isatty(STDIN_FILENO))
		return (readline("> "));
	return (read_line_fd(STDIN_FILENO));
}

static int	is_heredoc_dollar(const char *str, int i)
{
	if (str[i] != '$')
		return (0);
	if (!str[i + 1] || str[i + 1] == ' ' || str[i + 1] == '\t')
		return (0);
	return (1);
}

char	*expand_heredoc(const char *str, t_shell *shell)
{
	char	*result;
	char	*piece;
	int		i;

	result = NULL;
	i = 0;
	while (str[i])
	{
		if (is_heredoc_dollar(str, i))
			piece = resolve_dollar(str, &i, shell);
		else
			piece = char_to_str(shell, str[i++]);
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
