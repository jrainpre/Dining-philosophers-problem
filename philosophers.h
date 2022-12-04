/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonathanrainprechter <jonathanrainprech    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 10:55:16 by jrainpre          #+#    #+#             */
/*   Updated: 2022/12/04 14:24:27 by jonathanrai      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS
#define PHILOSOPHERS

#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
#include <string.h>

struct s_global;

typedef struct s_p
{
	int id;
	int fork_right;
	int fork_left;
	int has_forks;
	int eat_count;
	unsigned long last_eat;
	struct s_global *global; 
	pthread_t thread;
} t_p;

typedef struct s_global
{
	int nbr_ps;
	unsigned long tte;
	unsigned long ttd;
	pthread_mutex_t *lock_fork;
	char *forks;
	struct s_p *ps;
	int no_dead;
	int must_eat;
} t_global;


int	ft_atoi(const char *nptr);
int get_input(int argc, char **argv, t_global *global);




#endif
