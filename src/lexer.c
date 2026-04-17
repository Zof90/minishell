/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/17 13:48:21 by codespace         #+#    #+#             */
/*   Updated: 2026/04/17 17:05:46 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token *create_new_node_token(t_token_type type, char *value)
{
    t_token *new_node_token;

    new_node_token = malloc(sizeof(t_token));
    if (!new_node_token)
        return(NULL);
    new_node_token->value = ft_strdup(value);
    if (!new_node_token->value)
        return(NULL);
    new_node_token->type = type;
    new_node_token->next = NULL;
    return (new_node_token);   
}
void	token_lstadd_back(t_token **lst, t_token *new)
{
	t_env	*tmp;

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

t_token *build_token_list(char *str)
{
    t_token new_
}