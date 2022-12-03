#include "philosophers.h"
void *routine(void *ph);
int	malloc_philos(t_global *global);

int	main(int argc, char **argv)
{

	unsigned long	time_to_die;
	unsigned long	time_to_eat;
	pthread_mutex_t lock_fork;
	time_to_die = 1000;
	time_to_eat = 300;
		t_global test1;
	test1.tte = time_to_eat;
	test1.nbr_ps = 10;
	test1.lock_fork = &lock_fork;
	pthread_mutex_init(test1.lock_fork, NULL);
	malloc_philos(&test1);
}

int	malloc_philos(t_global *global)
{
	int i;
	int t_result;
	i = 0;
	 global->ps = malloc(sizeof(struct s_p) * global->nbr_ps);
	if (global->ps == NULL)
		return (0);
	i = 0;
	while (i < global->nbr_ps)
	{
		global->ps[i].id = i;
		global->ps[i].fork_right = i;
		global->ps[i].fork_left = (i + 1) % global->nbr_ps;
		global->ps[i].eat_count = 0;
		global->ps[i].last_eat = 0;
 
		t_result = pthread_create(&global->ps[i].thread, NULL, &routine, (void*)&(global->ps[i]));
		i++;
	}i = 0;
	while (i < global->nbr_ps)
	{
		pthread_join(global->ps[i].thread,NULL);
		i++;

		


	}

return(1);
}


void *routine(void *x)
{

	t_p *p;
	p = (t_p*)x;
		pthread_mutex_lock(p->global->lock_fork);
	printf("%d hallo\n", p->id);
	usleep(500);
		printf("%d bye\n", p->id);
	pthread_mutex_unlock(p->global->lock_fork);
	return(NULL);
}