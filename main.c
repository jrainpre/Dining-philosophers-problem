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
void	take_forks(t_p *p)
{
	if (p->global->forks[p->fork_left] && p->global->forks[p->fork_right])
	{
		printf("Philosopher %d has taken two forks.\n", p->id);
		p->global->forks[p->fork_right] = 0;
		p->global->forks[p->fork_left] = 0;
		p->has_forks = 1;
	}
}

void	start_eat(t_p *p)
{
	printf("Philosopher %d is eating.\n", p->id);
	usleep(p->global->tte);
	p->global->forks[p->fork_left] = 1;
	p->global->forks[p->fork_right] = 1;
	p->has_forks = 0;
	// p->last_eat = gettimeofday;
	printf("Philosopher %d has given the forks back.\n", p->id);
	printf("Philosopher %d is sleeping.\n", p->id); 
	usleep(1000000);
	printf("Philosopher %d is thinking.\n", p->id); 

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
	init_forks(global);
	i = 0;
	while (i < global->nbr_ps)
	{
		global->ps[i].id = i;
		global->ps[i].fork_right = i;
		global->ps[i].fork_left = (i + 1) % global->nbr_ps;
		global->ps[i].eat_count = 0;
		global->ps[i].last_eat = 0;
		global->ps[i].global = global;
		t_result = pthread_create(&global->ps[i].thread, NULL, &routine,
				(void *)&(global->ps[i]));
		i++;
	}
	i = 0;
	while (1)
	{
		int check_philo_starved(t_global *global);
	}
	
	while (i < global->nbr_ps)
	{
		pthread_join(global->ps[i].thread, NULL);
		int check_philo_starved(t_global *global);
		i++;
	}
	return (1);
}

void	*routine(void *x)
{
	t_p *p;
	p = (t_p *)x;
	p->has_forks = 0;
	while (1)
	{
		if (p->global->forks[p->fork_left] && p->global->forks[p->fork_right])
		{
			pthread_mutex_lock(p->global->lock_fork);
			// printf("%d hallo\n", p->id);
			take_forks(p);
			pthread_mutex_unlock(p->global->lock_fork);
		}
		if (p->has_forks)
			start_eat(p);
	}

	return (NULL);
}

int check_philo_starved(t_global *global)
{
	int i;
	unsigned long time;

	i = 0;
	// time = gettimeofday;
	while (i < global->nbr_ps)
	{
		if (time - global->ps[i].last_eat > global->tte)
		{
			printf("Philosopher %d has starved.\n", global->ps[i].id);
			global->no_dead = 0;
			return (0);
		}
		i++;
	}
	return (1);
}