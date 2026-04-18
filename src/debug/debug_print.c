/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_print.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azaytsev <azaytsev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/12 10:03:49 by azaytsev          #+#    #+#             */
/*   Updated: 2026/04/12 10:03:51 by azaytsev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static const char	*token_type_str(t_token_type type)
{
	if (type == TOK_WORD)
		return ("WORD");
	if (type == TOK_PIPE)
		return ("PIPE");
	if (type == TOK_REDIR_IN)
		return ("REDIR_IN");
	if (type == TOK_REDIR_OUT)
		return ("REDIR_OUT");
	if (type == TOK_HEREDOC)
		return ("HEREDOC");
	if (type == TOK_APPEND)
		return ("APPEND");
	return ("UNKNOWN");
}

void	debug_print_tokens(t_token *tokens)
{
	int	i;

	i = 0;
	printf("=== TOKENS ===\n");
	while (tokens)
	{
		printf("[%d] type=%-10s value=\"%s\"\n",
			i, token_type_str(tokens->type), tokens->value);
		tokens = tokens->next;
		i++;
	}
	printf("=== END ===\n");
}

static void	debug_print_redirs(t_redir *redirs)
{
	while (redirs)
	{
		printf("    redir: type=%-10s file=\"%s\" heredoc_quoted=%d\n",
			token_type_str(redirs->type), redirs->file,
			redirs->heredoc_quoted);
		redirs = redirs->next;
	}
}

void	debug_print_cmds(t_cmd *cmds)
{
	int	i;
	int	j;

	i = 0;
	printf("=== COMMANDS ===\n");
	while (cmds)
	{
		printf("[cmd %d]\n", i);
		if (cmds->args)
		{
			j = 0;
			while (cmds->args[j])
			{
				printf("    arg[%d]=\"%s\"\n", j, cmds->args[j]);
				j++;
			}
		}
		debug_print_redirs(cmds->redirs);
		cmds = cmds->next;
		i++;
	}
	printf("=== END ===\n");
}

void	debug_print_env(t_env *env)
{
	printf("=== ENV ===\n");
	while (env)
	{
		printf("%s=%s\n", env->key, env->value);
		env = env->next;
	}
	printf("=== END ===\n");
}
