/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbour <aelbour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 14:30:25 by aelbour           #+#    #+#             */
/*   Updated: 2025/07/13 11:00:55 by aelbour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


int init_mutexes(t_data *data)
{
	data->forks =  sem_open("forks", O_CREAT, 0644, data->num_philos);
	data->print_lock = sem_open("print", O_CREAT, 0644, 1);
	data->philos = malloc((data->num_philos) * sizeof(t_philo));
	if (!data->philos)
		return (0);
	return (1);
}

int	init_philo_tools(t_data *data)
{
	int	i;
	if(!init_mutexes(data))
		return (0);
	i = -1;
	while (++i < data->num_philos)
	{
		data->philos[i].id = i + 1;
		data->philos[i].meals_eaten = 0;
		data->philos[i].data = data;
	}
	return (1);
}

int	parse_init(int ac, char **av, t_data *data)
{
	int	error;

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
	if (!init_philo_tools(data))
		return (free(data->forks), 0);
	return (1);
}
