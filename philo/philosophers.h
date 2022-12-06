/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrainpre <jrainpre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 10:55:16 by jrainpre          #+#    #+#             */
/*   Updated: 2022/12/06 16:59:37 by jrainpre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

struct	s_global;

typedef struct s_p
{
	int				id;
	int				fork_right;
	int				fork_left;
	int				has_forks;
	int				eat_count;
	unsigned long	last_eat;
	struct s_global	*global;
	pthread_t		thread;
}					t_p;

typedef struct s_global
{
	int				nbr_ps;
	unsigned long	tte;
	unsigned long	ttd;
	unsigned long	tts;
	unsigned long	start_time;
	pthread_mutex_t	print;
	pthread_mutex_t	*singlefork;
	char			*forks;
	struct s_p		*ps;
	int				no_dead;
	int				must_eat;

}					t_global;

int					init_forks(t_global *global);
void				print_take_forks(t_p *p);
int					take_forks(t_p *p);
int					start_eat(t_p *p);
int					finish_process(t_global *global);
void				init_start_thread(t_global *global, int *t_result);
int					malloc_philos(t_global *global);
void				*routine(void *x);
int					check_philo_starved(t_global *global);
int					ft_atoi(const char *nptr);
unsigned long		get_time(void);
void				wait(unsigned long time_msec);
int					get_input(int argc, char **argv, t_global *global);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
int					check_number_valid(char *str);
int					check_inputs1_4(char **argv);
int					ft_isdigit(int c);

#endif
