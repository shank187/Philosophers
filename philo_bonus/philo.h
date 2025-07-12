/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbour <aelbour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 14:27:13 by aelbour           #+#    #+#             */
/*   Updated: 2025/07/12 16:13:12 by aelbour          ###   ########.fr       */
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
#include <semaphore.h>
#include <fcntl.h>  // Required for O_CREAT, O_EXCL
#include <sys/wait.h>
#include <errno.h>
#include <signal.h>


typedef struct s_data  t_data;


typedef struct s_philo
{
	int				id;
	pid_t			child_pid;
	atomic_int		meals_eaten;
	atomic_llong	last_meal_time;
	atomic_int		still_eating;
	t_data			*data;
}	t_philo;

typedef struct s_data
{
	int				num_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				meals_required;
	_Atomic int		stop;
	long long		start_time;
	sem_t	*forks;
	sem_t	*print_lock;
	t_philo			*philos;
}	t_data;

int			ft_atoi(const char *str, int *error);
int			parse_init(int ac, char **av, t_data *data);
long long	philo_get_time();
void	ft_usleep(size_t milliseconds, t_philo *philo);
int am_i_alive(t_philo *philo);
void	safe_printf(char *str, t_philo *philo);
void forks_pickup(t_philo * philo);
void eating_pastaa(t_philo *philo);
void clean_resources(t_data *data, int is_child);
void routine_philo(t_philo *philo);

#endif
