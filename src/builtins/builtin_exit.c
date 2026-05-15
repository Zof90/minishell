/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azaytsev <azaytsev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 09:00:00 by azaytsev          #+#    #+#             */
/*   Updated: 2026/04/28 09:00:00 by azaytsev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_numeric(const char *s)
{
	int	i;

	i = 0;
	if (s[0] == '+' || s[0] == '-')
		i = 1;
	if (!s[i])
		return (0);
	while (s[i])
	{
		if (s[i] < '0' || s[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

static int	accumulate_digits(const char *s, int i, unsigned long limit,
		unsigned long *val)
{
	while (s[i])
	{
		if (*val > (limit - (s[i] - '0')) / 10)
			return (0);
		*val = *val * 10 + (s[i] - '0');
		i++;
	}
	return (1);
}

static int	parse_long_safe(const char *s, long *out)
{
	int				i;
	int				neg;
	unsigned long	val;
	unsigned long	limit;

	i = 0;
	neg = (s[0] == '-');
	val = 0;
	if (s[0] == '+' || s[0] == '-')
		i = 1;
	if (neg)
		limit = 9223372036854775808UL;
	else
		limit = 9223372036854775807UL;
	if (!accumulate_digits(s, i, limit, &val))
		return (0);
	if (neg)
		*out = (long)(0UL - val);
	else
		*out = (long)val;
	return (1);
}

static int	exit_numeric_error(t_shell *shell, const char *arg)
{
	ft_putstr_fd("minishell: exit: ", 2);
	ft_putstr_fd((char *)arg, 2);
	ft_putendl_fd(": numeric argument required", 2);
	shell->running = 0;
	shell->exit_status = 2;
	return (2);
}

int	builtin_exit(t_shell *shell, char **args)
{
	long	val;

	ft_putendl_fd("exit", 2);
	if (!args[1])
	{
		shell->running = 0;
		return (shell->exit_status);
	}
	if (!is_numeric(args[1]) || !parse_long_safe(args[1], &val))
		return (exit_numeric_error(shell, args[1]));
	if (args[2])
	{
		print_error("exit", "too many arguments");
		return (1);
	}
	shell->running = 0;
	shell->exit_status = (unsigned char)val;
	return (shell->exit_status);
}
