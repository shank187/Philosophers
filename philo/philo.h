/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbour <aelbour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 14:27:13 by aelbour           #+#    #+#             */
/*   Updated: 2025/07/13 10:54:39 by aelbour          ###   ########.fr       */
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
	int				id;             
	atomic_int		meals_eaten;
	atomic_llong	last_meal_time;
	pthread_t		thread;

	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork; 
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
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_lock;
	pthread_mutex_t	death_lock;
	t_philo			*philos;
}	t_data;

int			ft_atoi(const char *str, int *error);
int			parse_init(int ac, char **av, t_data *data);
long long	philo_get_time();
int	ft_usleep(size_t milliseconds, t_data *data);
int are_u_alives(t_data *data);
int safe_printf(char *str, t_philo *philo);
void forks_pickup(t_philo * philo);
void eating_pastaa(t_philo *philo);
void	threads_waiter(t_data *data);
void ft_cleanup_forks(t_data *data, int up_to);
void ft_cleanup_table(t_data *data, int up_to);
void handle_crushes(t_data *data);

#endif
