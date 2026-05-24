/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_fields.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azaytsev <azaytsev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/21 09:00:00 by azaytsev          #+#    #+#             */
/*   Updated: 2026/05/24 15:00:00 by azaytsev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gc.h"
#include "minishell.h"

static char	*expanded_arg(const char *str, t_shell *shell)
{
	return (expand_str(str, shell));
}

static int	count_expanded_args(t_cmd *cmd, t_shell *shell, int *count)
{
	int		i;
	int		n;
	char	*value;

	i = 0;
	*count = 0;
	while (cmd->args && cmd->args[i])
	{
		value = expanded_arg(cmd->args[i], shell);
		if (!value)
			return (1);
		n = field_count_words(value);
		if (n == 0 && field_has_quotes(cmd->args[i]))
			n = 1;
		*count += n;
		i++;
	}
	return (0);
}

static int	add_expanded_arg(t_shell *shell, char **args, char *src, int *j)
{
	char	*value;

	value = expanded_arg(src, shell);
	if (!value)
		return (1);
	if (*value == '\0' && field_has_quotes(src))
	{
		args[(*j)++] = value;
		return (0);
	}
	return (field_append_words(shell, args, j, value));
}

int	expand_args(t_cmd *cmd, t_shell *shell)
{
	int		i;
	int		j;
	int		count;
	char	**args;

	if (count_expanded_args(cmd, shell, &count))
		return (1);
	args = gc_malloc(shell, sizeof(char *) * (count + 1));
	if (!args)
		return (1);
	i = 0;
	j = 0;
	while (cmd->args && cmd->args[i])
	{
		if (add_expanded_arg(shell, args, cmd->args[i], &j))
			return (1);
		i++;
	}
	args[j] = NULL;
	cmd->args = args;
	return (0);
}
