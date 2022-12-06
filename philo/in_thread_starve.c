/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   in_thread_starve.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrainpre <jrainpre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 15:30:07 by jrainpre          #+#    #+#             */
/*   Updated: 2022/12/06 17:00:17 by jrainpre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	print_end_message(t_global *global, char *message, int *i)
{
	unsigned long	time;

	time = get_time() - global->start_time;
	pthread_mutex_lock(&global->print);
	printf("%ld %d %s", time, global->ps[*i].id + 1, message);
	global->no_dead = 0;
	pthread_mutex_unlock(&global->print);
}

int	check_philo_starved(t_global *global)
{
	int				i;
	unsigned long	time;
	int				eat_count;

	i = 0;
	eat_count = 0;
	time = get_time();
	while (i < global->nbr_ps)
	{
		if ((time - (global->ps[i].last_eat)) > global->ttd)
		{
			print_end_message(global, "died\n", &i);
			return (0);
		}
		if (global->ps[i].eat_count >= global->must_eat)
			eat_count++;
		i++;
		if (eat_count >= global->nbr_ps && global->must_eat != -1)
		{
			print_end_message(global, "Everyone ate enough\n", &i);
			return (0);
		}
	}
	return (1);
}

unsigned long	get_time(void)
{
	struct timeval	time;
	unsigned long	time_msec;

	gettimeofday(&time, NULL);
	time_msec = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	return (time_msec);
}

void	wait(unsigned long time_msec)
{
	usleep(1000 * time_msec);
}
