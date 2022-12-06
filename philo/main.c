/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrainpre <jrainpre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 17:00:28 by jrainpre          #+#    #+#             */
/*   Updated: 2022/12/06 17:08:01 by jrainpre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int argc, char **argv)
{
	t_global		global;

	global.no_dead = 1;
	if (get_input(argc, argv, &global) == 0)
		return (0);
	if (malloc_philos(&global) != 1)
	{
		printf("Error System");
		return (0);
	}
	if (finish_process(&global) != 1)
	{
		printf("Error System");
		return (0);
	}
	return (0);
}

int	finish_process(t_global *global)
{
	int	i;
	int	t_result;

	i = 0;
	t_result = 0;
	while (global->no_dead)
		check_philo_starved(global);
	i = 0;
	while (i < global->nbr_ps)
		if (pthread_join(global->ps[i++].thread, NULL) != 0)
			return (0);
	while (i < global->nbr_ps)
		if (pthread_mutex_destroy(&global->singlefork[i++]) != 0)
			return (0);
	if (pthread_mutex_destroy(&global->print) != 0)
		return (0);
	free(global->forks);
	free(global->singlefork);
	free(global->ps);
	return (1);
}

void	init_start_thread(t_global *global, int *t_result)
{
	int	i;

	i = 0;
	while (i < global->nbr_ps)
	{
		global->ps[i].id = i;
		global->ps[i].fork_right = i;
		global->ps[i].fork_left = (i + 1) % global->nbr_ps;
		global->ps[i].eat_count = 0;
		global->ps[i].last_eat = get_time();
		global->ps[i].global = global;
		*t_result += pthread_create(&global->ps[i].thread, NULL, &routine, \
				(void *)&(global->ps[i]));
		i++;
	}
}

int	malloc_philos(t_global *global)
{
	int	i;
	int	t_result;

	t_result = 0;
	global->ps = malloc(sizeof(struct s_p) * global->nbr_ps);
	global->singlefork = malloc(sizeof(pthread_mutex_t) * global->nbr_ps);
	if (global->ps == NULL || global->ps == NULL)
		return (0);
	t_result += pthread_mutex_init(&global->print, NULL);
	global->start_time = get_time();
	t_result += init_forks(global);
	i = 0;
	while (i < global->nbr_ps)
		t_result += pthread_mutex_init(&global->singlefork[i++], NULL);
	init_start_thread(global, &t_result);
	if (t_result != 0)
		return (0);
	return (1);
}
