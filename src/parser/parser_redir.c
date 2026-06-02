/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azaytsev <azaytsev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/12 10:05:50 by azaytsev          #+#    #+#             */
/*   Updated: 2026/05/04 16:36:16 by azaytsev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gc.h"
#include "minishell.h"

static void	redir_add_back(t_redir **list, t_redir *new_redir)
{
	t_redir	*last;

	if (!new_redir)
		return ;
	if (!*list)
	{
		*list = new_redir;
		return ;
	}
	last = *list;
	while (last->next)
		last = last->next;
	last->next = new_redir;
}

static int	has_quotes(const char *str)
{
	while (*str)
	{
		if (*str == '\'' || *str == '"')
			return (1);
		str++;
	}
	return (0);
}

static char	*strip_delimiter_quotes(t_shell *shell, const char *str)
{
	char	*result;
	int		i;
	int		j;
	char	quote;

	result = gc_malloc(shell, ft_strlen(str) + 1);
	if (!result)
		return (NULL);
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '"')
		{
			quote = str[i++];
			while (str[i] && str[i] != quote)
				result[j++] = str[i++];
			if (str[i])
				i++;
		}
		else
			result[j++] = str[i++];
	}
	result[j] = '\0';
	return (result);
}

t_redir	*create_redir(t_shell *shell, t_token_type type, const char *file_val)
{
	t_redir	*redir;

	redir = gc_malloc(shell, sizeof(t_redir));
	if (!redir)
		return (NULL);
	redir->type = type;
	redir->fd = -1;
	redir->heredoc_quoted = 0;
	redir->heredoc_content = NULL;
	redir->next = NULL;
	if (type == TOK_HEREDOC)
	{
		redir->heredoc_quoted = has_quotes(file_val);
		redir->file = strip_delimiter_quotes(shell, file_val);
	}
	else
		redir->file = gc_strdup(shell, file_val);
	if (!redir->file)
		return (NULL);
	return (redir);
}

int	parse_redir(t_shell *shell, t_token **cur, t_redir **redirs)
{
	t_token	*tok;
	t_redir	*redir;

	tok = *cur;
	redir = create_redir(shell, tok->type, tok->next->value);
	if (!redir)
		return (1);
	if (tok->value[0] >= '0' && tok->value[0] <= '9')
		redir->fd = ft_atoi(tok->value);
	redir_add_back(redirs, redir);
	*cur = tok->next->next;
	return (0);
}
