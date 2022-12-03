/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrainpre <jrainpre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 10:55:16 by jrainpre          #+#    #+#             */
/*   Updated: 2022/12/02 16:21:05 by jrainpre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS
#define PHILOSOPHERS

#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>

struct s_global;

typedef struct s_p
{
	int id;
	int fork_right;
	int fork_left;
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
} t_global;







#endif
