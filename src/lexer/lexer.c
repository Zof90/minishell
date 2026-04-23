/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zof <zof@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/22 17:53:21 by zof               #+#    #+#             */
/*   Updated: 2026/04/23 15:31:20 by zof              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	set_type(t_token *new_node)
{
	if (*new_node->value == '<')
		new_node->type = TOK_REDIR_IN;
	else if (*new_node->value == '>')
		new_node->type = TOK_REDIR_OUT;
	else if (*new_node->value == '>>')
		new_node->type = TOK_APPEND;
	else if (*new_node->value == '<<')
		new_node->type = TOK_HEREDOC;
	else if (*new_node->value == '|')
		new_node->type = TOK_PIPE;
	else
		new_node->type = TOK_WORD;
}
static char	*new_word_str(char *str, int len)
{
	char	*word;

	word = malloc(len + 1);
	if (!word)
		return (NULL);
	ft_strlcpy(word, str, len);
	return (word);
}
static void	ft_lstadd_back(t_token **lst, t_token *new)
{
	t_token	*tmp;

	if (!new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	tmp = *lst;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}
static t_token	*new_token(t_shell *shell, char *word, int len)
{
	t_token	*new_node;
	t_token	*token;

	new_node = gc_malloc(shell, sizeof(new_node));
	if (!new_node)
		return (NULL);
	new_node->value = gc_substr(shell, word, 0, len);
	if (!new_node->value)
		return (NULL);
	set_type(new_node);
	new_node->next = NULL;
	lst_add_back_token(&token, new_node);
	return (token);
}
t_token	*lexer(t_shell *shell, char *line)
{
	int		i;
	int		len;
	t_token	*token;
	char	*word;

	i = 0;
	if (!line)
		return (NULL);
	while (line[i])
	{
		len = token_size(line);
		if (len == -1)
			return (NULL);
		word = new_word_str(&line[i], len);
		if (!word)
			return (NULL);
		token = new_token(shell, word, len);
		if (!token)
			return (free(word), NULL);
		free(word);
		i = i + len + 1;
	}
}
