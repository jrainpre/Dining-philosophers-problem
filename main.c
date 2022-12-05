#include "philosophers.h"
void	*routine(void *ph);
int		malloc_philos(t_global *global);
int check_philo_starved(t_global *global);

int	init_forks(t_global *global)
{
	int	i;

	i = 0;
	global->forks = malloc(sizeof(char) * global->nbr_ps);
	if (!global->forks)
		return (0);
	while (i < global->nbr_ps)
	{
		global->forks[i] = 1;
		i++;
	}
	return (1);
}
int	take_forks(t_p *p)
{
	unsigned long time;

	if (p->global->forks[p->fork_left] && p->global->forks[p->fork_right])
	{
		pthread_mutex_lock(&p->global->singlefork[p->fork_left]);
		pthread_mutex_lock(&p->global->singlefork[p->fork_right]);

		time = get_time() - p->global->start_time;
			if (p->global->no_dead)
		printf("%ld %d has taken a fork\n",time, p->id + 1);
		p->global->forks[p->fork_right] = 0;
		time = get_time() - p->global->start_time;
			if (p->global->no_dead)
		printf("%ld %d has taken a fork\n",time, p->id + 1);
		p->global->forks[p->fork_left] = 0;
		p->has_forks = 1;
		start_eat(p);
		pthread_mutex_unlock(&p->global->singlefork[p->fork_left]);
		pthread_mutex_unlock(&p->global->singlefork[p->fork_right]);
		return (0);
	}
	return (1);
}

void	start_eat(t_p *p)
{
	unsigned long time;

	time = get_time() - p->global->start_time;
	if (p->global->no_dead)
		printf("%ld %d is eating\n", time, p->id + 1);
	p->last_eat = get_time();
	p->eat_count++;
	p->global->forks[p->fork_left] = 1;
	p->global->forks[p->fork_right] = 1;
	wait(p->global->tte);
	p->has_forks = 0;
}
int	main(int argc, char **argv)
{
	pthread_mutex_t	lock_fork;
	t_global		global;

	get_input(argc, argv,&global);
	global.lock_fork = &lock_fork;
	pthread_mutex_init(global.lock_fork, NULL);
	malloc_philos(&global);
}

int	malloc_philos(t_global *global)
{
	int	i;
	int	t_result;

	i = 0;
	global->ps = malloc(sizeof(struct s_p) * global->nbr_ps);
	if (global->ps == NULL)
		return (0);
	global->singlefork = malloc(sizeof(pthread_mutex_t) * global->nbr_ps);
	global->start_time = get_time();
	init_forks(global);
	i = 0;
	while (i < global->nbr_ps)
	{
		pthread_mutex_init(&global->singlefork[i], NULL);
		i++;
	}
	i = 0;
	while (i < global->nbr_ps)
	{
		global->ps[i].id = i;
		global->ps[i].fork_right = i;
		global->ps[i].fork_left = (i + 1) % global->nbr_ps;
		global->ps[i].eat_count = 0;
		global->ps[i].last_eat = get_time();
		global->ps[i].global = global;
		t_result = pthread_create(&global->ps[i].thread, NULL, &routine,
				(void *)&(global->ps[i]));
		i++;
	}
	i = 0;
	while (1)
	{
		if (!check_philo_starved(global))
			return(0);
	}
	
	while (i < global->nbr_ps)
	{
		check_philo_starved(global);
		pthread_join(global->ps[i].thread, NULL);
		i++;
	}
	return (1);
}

void	*routine(void *x)
{
	t_p *p;
	p = (t_p *)x;
	p->has_forks = 0;
	unsigned long time;
	if (p->id % 2 != 1)
        wait(1);
	while (1)
	{
		while (take_forks(p))
			usleep(0);
		time = get_time() - p->global->start_time;
		if (p->global->no_dead)
			printf("%ld %d is sleeping\n", time, p->id + 1); 
		wait(p->global->tts);
		time = get_time() - p->global->start_time;
		if (p->global->no_dead)
			printf("%ld %d is thinking\n", time, p->id + 1); 

	}
	return (NULL);
}

int check_philo_starved(t_global *global)
{
	int i;
	unsigned long time;
	int eat_count;

	i = 0;
	time = get_time();
	while (i < global->nbr_ps)
	{
		if ((time - (global->ps[i].last_eat)) > global->ttd)
		{
			time = get_time() - global->start_time;
			printf("%ld %d died\n", time, global->ps[i].id + 1);
			global->no_dead = 0;
			return (0);
		}
		if (global->ps[i].eat_count >= global->must_eat)
			eat_count++;
		i++;
		if (eat_count >= global->nbr_ps && eat_count != -1)
		{
			time = get_time() - global->start_time;
			printf("%ld  Everyone ate enough\n", time);
			global->no_dead = 0;
			return (0);
		}
	}
	return (1);
}