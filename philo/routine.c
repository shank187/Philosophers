/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbour <aelbour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 13:23:26 by aelbour           #+#    #+#             */
/*   Updated: 2025/07/12 15:57:04 by aelbour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void forks_pickup(t_philo * philo)
{
	if (philo->id == philo->data->num_philos) 
	{
		pthread_mutex_lock(philo->right_fork);
		safe_printf("has taken a fork", philo);
		pthread_mutex_lock(philo->left_fork);
		if(safe_printf("has taken a fork", philo))
			philo->still_eating = 1;
	}
	else
	{
		pthread_mutex_lock(philo->left_fork);
		safe_printf("has taken a fork", philo);
		pthread_mutex_lock(philo->right_fork);
		if(safe_printf("has taken a fork", philo))
			philo->still_eating = 1;
	}
}

void eating_pastaa(t_philo *philo)
{
	safe_printf("is eating", philo);
	if (!ft_usleep(philo->data->time_to_eat * 1000, philo->data))
	{
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
		pthread_exit(NULL);
	}
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	philo->last_meal_time = philo_get_time();
	philo->meals_eaten++;
	philo->still_eating = 0;
}

int	search_for_dead_bodies(t_data *data)
{
	int	i;

	i = data->num_philos;
	while (--i >= 0)
	{
		if (philo_get_time() - data->philos[i].last_meal_time  \
		> data->time_to_die && !data->philos[i].still_eating)
		{			
			pthread_mutex_lock(&data->death_lock);
			data->stop = 1;
			pthread_mutex_unlock(&data->death_lock);
			pthread_mutex_lock(&data->print_lock);
			printf("%lld %i died\n", philo_get_time() - data->start_time, data->philos[i].id);
			pthread_mutex_unlock(&data->print_lock);
			return (1);
		}
	}
	return (0);
}

int is_all_satisfied(t_data *data)
{
	int	i;

	if (data->meals_required != 0)
	{
		i = -1;
		while (++i < data->num_philos && data->philos[i].meals_eaten >= data->meals_required);
		if (i == data->num_philos)
		{
			data->stop = 1;
			return(1);
		}
	}
	return(0);
}

void	threads_guard(t_data *data)
{
	while (1)
	{
		if (search_for_dead_bodies(data))
			break ;
		if (is_all_satisfied(data))
			break;
	}
}
