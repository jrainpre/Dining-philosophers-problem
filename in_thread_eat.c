/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   in_thread_eat.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrainpre <jrainpre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 15:30:07 by jrainpre          #+#    #+#             */
/*   Updated: 2022/12/06 16:00:26 by jrainpre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	take_forks(t_p *p)
{
	if (p->global->forks[p->fork_left] && p->global->forks[p->fork_right])
	{
		pthread_mutex_lock(&p->global->singlefork[p->fork_left]);
		pthread_mutex_lock(&p->global->singlefork[p->fork_right]);
		print_take_forks(p);
		p->global->forks[p->fork_right] = 0;
		print_take_forks(p);
		p->global->forks[p->fork_left] = 0;
		p->has_forks = 1;
		start_eat(p);
		pthread_mutex_unlock(&p->global->singlefork[p->fork_left]);
		pthread_mutex_unlock(&p->global->singlefork[p->fork_right]);
		return (0);
	}
	return (1);
}

void	print_take_forks(t_p *p)
{
	unsigned long	time;

	time = get_time() - p->global->start_time;
	pthread_mutex_lock(&p->global->print);
	if (p->global->no_dead == 1)
		printf("%ld %d has taken a fork\n", time, p->id + 1);
	pthread_mutex_unlock(&p->global->print);
}

int	init_forks(t_global *global)
{
	int	i;

	i = 0;
	global->forks = malloc(sizeof(char) * global->nbr_ps);
	if (!global->forks)
		return (1);
	while (i < global->nbr_ps)
	{
		global->forks[i] = 1;
		i++;
	}
	return (0);
}

int	start_eat(t_p *p)
{
	unsigned long	time;

	time = get_time() - p->global->start_time;
	pthread_mutex_lock(&p->global->print);
	if (p->global->no_dead)
		printf("%ld %d is eating\n", time, p->id + 1);
	pthread_mutex_unlock(&p->global->print);
	p->last_eat = get_time();
	p->eat_count++;
	p->global->forks[p->fork_left] = 1;
	p->global->forks[p->fork_right] = 1;
	wait(p->global->tte);
	p->has_forks = 0;
	return (0);
}

void	*routine(void *x)
{
	t_p				*p;
	unsigned long	time;

	p = (t_p *)x;
	p->has_forks = 0;
	if (p->id % 2 != 1)
		wait(1);
	while (p->global->no_dead)
	{
		while (take_forks(p) == 1)
			usleep(0);
		time = get_time() - p->global->start_time;
		pthread_mutex_lock(&p->global->print);
		if (p->global->no_dead == 1)
			printf("%ld %d is sleeping\n", time, p->id + 1);
		pthread_mutex_unlock(&p->global->print);
		wait(p->global->tts);
		time = get_time() - p->global->start_time;
		pthread_mutex_lock(&p->global->print);
		if (p->global->no_dead == 1)
			printf("%ld %d is thinking\n", time, p->id + 1);
		pthread_mutex_unlock(&p->global->print);
	}
	return (NULL);
}
