/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getInput.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrainpre <jrainpre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 16:58:06 by jrainpre          #+#    #+#             */
/*   Updated: 2022/12/06 17:18:39 by jrainpre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	get_input(int argc, char **argv, t_global *global)
{
	if (argc < 5 || argc > 6)
	{
		printf("Not enogh arguments");
		return (0);
	}
	if (argc >= 5)
	{
		if (!check_inputs1_4(argv))
			return (0);
		global->nbr_ps = ft_atoi(argv[1]);
		global->ttd = ft_atoi(argv[2]);
		global->tte = ft_atoi(argv[3]);
		global->tts = ft_atoi(argv[4]);
		global->must_eat = -1;
	}
	if (argc == 6)
	{
		if (!check_number_valid(argv[5]))
		{
			printf("Given arguments are invalid");
			return (0);
		}
		global->must_eat = ft_atoi(argv[5]);
	}
	return (1);
}

int	check_inputs1_4(char **argv)
{
	int	temp;

	if (!(check_number_valid(argv[1]) && check_number_valid(argv[2])
			&& check_number_valid(argv[3]) && check_number_valid(argv[4])))
	{
		printf("Given arguments are invalid");
		return (0);
	}
	temp = ft_atoi(argv[1]);
	if (temp == 0)
	{
		printf("There has to be at least on philosopher.");
		return (0);
	}
	if (temp == 1)
	{
		printf("0 1 died");
		return (0);
	}
	return (1);
}

int	check_number_valid(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!(str[i] == '+' || ft_isdigit(str[i])))
			return (0);
		i++;
	}
	if (ft_atoi(str) == -1)
	{
		if (ft_strncmp("-1", str, 2) != 0)
			return (0);
	}
	return (1);
}
