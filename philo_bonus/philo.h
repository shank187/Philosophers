/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbour <aelbour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 14:27:13 by aelbour           #+#    #+#             */
/*   Updated: 2025/07/19 10:44:29 by aelbour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <semaphore.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <errno.h>
# include <signal.h>
# include <pthread.h>
# include <stdatomic.h> 

typedef struct s_data	t_data;

typedef struct s_philo
{
	int				id;
	pid_t			child_pid;
	int				meals_eaten;
	atomic_llong	last_meal_time;
	t_data			*data;
}	t_philo;

typedef struct s_data
{
	int			num_philos;
	int			time_to_die;
	int			time_to_eat;
	int			time_to_sleep;
	int			meals_required;
	int			stop;
	long long	start_time;
	sem_t		*forks;
	sem_t		*print_lock;
	t_philo		*philos;
}	t_data;

int			ft_atoi(const char *str, int *error);
int			parse_init(int ac, char **av, t_data *data);
long long	philo_get_time(void);
void		ft_usleep(size_t milliseconds, t_philo *philo);
int			am_i_alive(t_philo *philo);
void		safe_printf(char *str, t_philo *philo);
void		forks_pickup(t_philo *philo);
void		eating_pastaa(t_philo *philo);
void		clean_resources(t_data *data, int is_child);
void		routine_philo(t_philo *philo);
void		handle_crushes(t_data *data, int is_child);

#endif
