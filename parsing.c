/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbour <aelbour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 14:30:25 by aelbour           #+#    #+#             */
/*   Updated: 2025/07/10 11:25:54 by aelbour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"



int parse_init(int ac, char **av, t_data *data)
{
	long long i;
	int error;

	i = 0;
	error = 0;
	if (ac != 5 && ac != 6)
		return (0);
	data->num_philos = ft_atoi(av[1], &error);
	data->time_to_die = ft_atoi(av[2], &error);
	data->time_to_eat = ft_atoi(av[3], &error);
	data->time_to_sleep = ft_atoi(av[4], &error);
	data->meals_required = 0;
	data->stop = 0;
	if (av[5])
		data->meals_required = ft_atoi(av[5], &error);
	if (error || data->num_philos > 200)
		return (0);
	data->forks = malloc(data->num_philos * sizeof(pthread_mutex_t));
	if (!data->forks)
		return (0);
	i = -1;
	while(++i < data->num_philos)
		pthread_mutex_init(&(data->forks[i]), NULL);
	pthread_mutex_init(&(data->print_lock), NULL);
	data->philos = malloc((data->num_philos) * sizeof(t_philo));
	if (!data->philos)
		return (0);
	i = -1;
	while (++i < data->num_philos)
	{
		data->philos[i].id = i + 1;
		data->philos[i].meals_eaten = 0;
		data->philos[i].right_fork = &data->forks[i];
		data->philos[i].left_fork = &data->forks[(i + 1) % data->num_philos];
		data->philos[i].data = data;
	}
	return (1);

}
