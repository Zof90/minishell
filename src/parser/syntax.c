/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azaytsev <azaytsev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/12 10:06:07 by azaytsev          #+#    #+#             */
/*   Updated: 2026/04/12 10:06:09 by azaytsev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_redir(t_token_type type)
{
	return (type == TOK_REDIR_IN || type == TOK_REDIR_OUT
		|| type == TOK_HEREDOC || type == TOK_APPEND);
}

static int	syntax_error(const char *token_val)
{
	const char	*p[4];

	p[0] = "minishell: syntax error near unexpected token `";
	p[1] = token_val;
	p[2] = "'\n";
	p[3] = NULL;
	print_error_parts(p);
	return (2);
}

static int	check_token(t_token *cur)
{
	if (is_redir(cur->type) && (!cur->next
			|| cur->next->type != TOK_WORD))
	{
		if (cur->next)
			return (syntax_error(cur->next->value));
		return (syntax_error("newline"));
	}
	if (cur->type == TOK_PIPE && (!cur->next
			|| cur->next->type == TOK_PIPE))
	{
		if (cur->next)
			return (syntax_error(cur->next->value));
		return (syntax_error("|"));
	}
	return (0);
}

int	syntax_check(t_token *tokens)
{
	t_token	*cur;
	int		result;

	if (!tokens)
		return (0);
	if (tokens->type == TOK_PIPE)
		return (syntax_error(tokens->value));
	cur = tokens;
	while (cur)
	{
		result = check_token(cur);
		if (result)
			return (result);
		cur = cur->next;
	}
	return (0);
}
