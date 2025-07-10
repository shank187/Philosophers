/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbour <aelbour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 14:27:13 by aelbour           #+#    #+#             */
/*   Updated: 2025/07/10 11:26:41 by aelbour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
#include <sys/time.h>
#include <stdatomic.h> 

typedef struct s_data  t_data;


typedef struct s_philo
{
	int             id;             // philosopher ID (1-based)
	_Atomic			int             meals_eaten;    // how many times this philosopher ate
	_Atomic long long       last_meal_time; // timestamp of last meal (ms)
	pthread_t       thread;         // thread handle

	pthread_mutex_t	*left_fork;     // pointer to the left fork (mutex)
	pthread_mutex_t	*right_fork;// pointer to the right fork (mutex)
	t_data			*data;    
}	t_philo;

typedef struct s_data
{
	int             num_philos;     // number of philosophers
	int             time_to_die;
	int             time_to_eat;
	int             time_to_sleep;
	int             meals_required; // optional arg: nb of meals before stopping
	_Atomic int             stop;   // flag to end simulation
	long long       start_time;     // simulation start time (ms)
	pthread_mutex_t	*forks;         // array of N mutexes for forks
	pthread_mutex_t	print_lock;    // to synchronize output
	t_philo         *philos;        // array of philosophers
}	t_data;

int			ft_atoi(const char *str, int *error);
int			parse_init(int ac, char **av, t_data *data);
long long	philo_get_time();
int	ft_usleep(size_t milliseconds, t_data *data);
int check_for_deads(t_data *data);

#endif
