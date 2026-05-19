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

static int	skip_ws(const char *s, int i)
{
	while (s[i] == ' ' || s[i] == '\t')
		i++;
	return (i);
}

static int	accumulate_digits(const char *s, int *i, unsigned long limit,
		unsigned long *val)
{
	int	digits;

	digits = 0;
	while (s[*i] >= '0' && s[*i] <= '9')
	{
		if (*val > (limit - (s[*i] - '0')) / 10)
			return (0);
		*val = *val * 10 + (s[*i] - '0');
		(*i)++;
		digits++;
	}
	return (digits);
}

static int	parse_long_safe(const char *s, long *out)
{
	int				i;
	int				neg;
	unsigned long	val;
	unsigned long	limit;

	i = skip_ws(s, 0);
	neg = (s[i] == '-');
	if (s[i] == '+' || s[i] == '-')
		i++;
	val = 0;
	if (neg)
		limit = 9223372036854775808UL;
	else
		limit = 9223372036854775807UL;
	if (!accumulate_digits(s, &i, limit, &val))
		return (0);
	if (s[skip_ws(s, i)])
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
	if (!parse_long_safe(args[1], &val))
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
