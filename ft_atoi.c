/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonathanrainprechter <jonathanrainprech    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 11:50:50 by jrainpre          #+#    #+#             */
/*   Updated: 2022/12/04 14:40:11 by jonathanrai      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



int	ft_atoi(const char *nptr)
{
	int		i;
	int		sign;
	long	nb;

	nb = 0;
	sign = 1;
	i = 0;
	while ((nptr[i] >= '\t' && nptr[i] <= '\r') || nptr[i] == ' ')
		i++;
	if (nptr[i] == '+' || nptr[i] == '-')
	{
		if (nptr[i] == '-')
			sign *= -1;
		i++;
	}
	while ('0' <= nptr[i] && nptr[i] <= '9')
	{
		nb = nb * 10 + nptr[i] - '0';
		if (nb * sign > 2147483647)
			return (-1);
		if (nb * sign < -2147483648)
			return (-1);
		i++;
	}
	return (nb * sign);
}
/*
#include <stdio.h>
#include <string.h>
int	main(void)
{
printf("%d\n",ft_atoi("945"));
printf("%d\n",ft_atoi("\t\v\f\r\n \f- \f\t\n\r    06050"));
printf("%d\n",atoi("945"));
printf("%d\n",atoi("-2147483649"));
}
*/