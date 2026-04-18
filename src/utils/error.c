/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azaytsev <azaytsev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/18 13:07:20 by azaytsev          #+#    #+#             */
/*   Updated: 2026/04/18 13:07:20 by azaytsev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_error(const char *context, const char *message)
{
	ft_putstr_fd("minishell: ", 2);
	if (context)
	{
		ft_putstr_fd((char *)context, 2);
		ft_putstr_fd(": ", 2);
	}
	ft_putendl_fd((char *)message, 2);
}
