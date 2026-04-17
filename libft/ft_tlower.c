/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tlower.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schouite <schouite@student.42paris.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/15 17:54:47 by schouite          #+#    #+#             */
/*   Updated: 2025/11/16 18:40:44 by schouite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_tolower(int c)
{
	if (c >= 65 && c <= 90)
		c += 32;
	return (c);
}
/* #include<stdio.h>
int	main(void)
{
	char	*str = "JE SUIS 9 MOI";
	int	i;
	int j;

	i = 0;
	j = 0;
	while(str[i])
	{
		j = ft_tolower(str[i]);
		printf("%c",j);
		i++;
	}
	printf("\n");
} */
