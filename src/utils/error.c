/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schouite <schouite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/18 13:07:20 by azaytsev          #+#    #+#             */
/*   Updated: 2026/06/03 21:22:26 by schouite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gc.h"
#include "minishell.h"

static size_t	append_part(char *dst, size_t pos, const char *src)
{
	size_t	i;

	i = 0;
	while (src && src[i])
		dst[pos++] = src[i++];
	return (pos);
}

void	print_error(const char *context, const char *message)
{
	size_t	len;
	size_t	pos;
	char	*line;

	len = 12 + ft_strlen(message);
	if (context)
	{
		len += ft_strlen(context) + 2;
	}
	line = malloc(len + 1);
	if (!line)
		return ;
	pos = append_part(line, 0, "minishell: ");
	if (context)
	{
		pos = append_part(line, pos, context);
		pos = append_part(line, pos, ": ");
	}
	pos = append_part(line, pos, message);
	line[pos++] = '\n';
	line[pos] = '\0';
	write(2, line, pos);
	free(line);
}

static int	has_search_path(t_shell *shell)
{
	char	*path_env;

	path_env = env_get(shell->env, "PATH");
	if (!path_env || !*path_env)
		return (0);
	return (1);
}

static int	probe_path(const char *name)
{
	struct stat	st;

	if (stat(name, &st) != 0)
		return (0);
	if (S_ISDIR(st.st_mode))
	{
		print_error(name, "Is a directory");
		return (126);
	}
	if (access(name, X_OK) != 0)
	{
		print_error(name, "Permission denied");
		return (126);
	}
	print_error(name, strerror(errno));
	return (126);
}

void	child_exit_error(t_shell *shell, char *name)
{
	int	code;

	if (ft_strchr(name, '/') || !has_search_path(shell))
	{
		code = probe_path(name);
		if (code)
			exit(code);
		print_error(name, "No such file or directory");
		exit(127);
	}
	print_error(name, "command not found");
	gc_free(shell);
	free_env(shell->env);
	free(shell->line);
	exit(127);
}
