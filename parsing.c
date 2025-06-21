/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbour <aelbour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 14:30:25 by aelbour           #+#    #+#             */
/*   Updated: 2025/06/21 16:09:19 by aelbour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long philo_get_time()
{
	struct timeval tv;
	long long ms_time;

	if(gettimeofday(&tv, NULL) == -1)
		return(-1);
	ms_time = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	return(ms_time);
}

int parse_init(int ac, char **av, t_data *data)
{
	long long i;

	int error;

	i = 0;
	error = 0;
	if (ac != 4 || ac != 5)
		return (0);
	data->num_philos = ft_atoi(av[1], &error);
	data->time_to_die = ft_atoi(av[2], &error);
	data->time_to_eat = ft_atoi(av[3], &error);
	data->time_to_sleep = ft_atoi(av[4], &error);
	data->meals_required = 3;
	data->someone_died = 0;
	if (av[5])
		data->meals_required = ft_atoi(av[5], &error);
	if(error || data->num_philos > 61772)
		return (0);
	data->forks = malloc(data->num_philos * sizeof(pthread_mutex_t));
	if(!data->forks)
		return (0);
	data->philos = malloc((data->num_philos) * sizeof(t_philo));
	if(!data->philos)
		return (0);
	while(i < data->num_philos)
	{
		data->philos[i].id = i + 1;
		data->philos[i].meals_eaten = 0;
		data->philos[i].right_fork = &data->forks[i];
		data->philos[i].left_fork = &data->forks[(i + 1) % data->num_philos];
		data->philos[i].last_meal_time = philo_get_time();
	}
	i = -1;
	while(++i < data->num_philos)
		pthread_join(data->philos[i].thread, NULL);
}
