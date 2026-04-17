/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schouite <schouite@student.42paris.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/15 17:37:44 by schouite          #+#    #+#             */
/*   Updated: 2025/11/16 18:40:48 by schouite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_toupper(int c)
{
	if (c >= 97 && c <= 122)
		c -= 32;
	return (c);
}
/* #include<stdio.h>
int	main(void)
{
	char	*str;
	int		i;
	int		j;

	str = "je suis 9 moi";
	i = 0;
	j = 0;
	while(str[i])
	{
		j = ft_toupper(str[i]);
		printf("%c",j);
		i++;
	}
	printf("\n");
}
 */
