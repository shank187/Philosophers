/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbour <aelbour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 13:23:26 by aelbour           #+#    #+#             */
/*   Updated: 2025/07/13 10:55:24 by aelbour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void forks_pickup(t_philo * philo)
{
	if (philo->id == philo->data->num_philos) 
	{
		if (pthread_mutex_lock(philo->right_fork))
			handle_crushes(philo->data);
		safe_printf("has taken a fork", philo);
		if (pthread_mutex_lock(philo->left_fork))
			handle_crushes(philo->data);
		safe_printf("has taken a fork", philo);
	}
	else
	{
		if (pthread_mutex_lock(philo->left_fork))
			handle_crushes(philo->data);
		safe_printf("has taken a fork", philo);
		if (pthread_mutex_lock(philo->right_fork))
			handle_crushes(philo->data);
		safe_printf("has taken a fork", philo);
	}
}

void eating_pastaa(t_philo *philo)
{
	safe_printf("is eating", philo);
	philo->last_meal_time = philo_get_time();
	if (!ft_usleep(philo->data->time_to_eat , philo->data))
	{
		if (pthread_mutex_unlock(philo->right_fork))
			handle_crushes(philo->data);
		if (pthread_mutex_unlock(philo->left_fork))
			handle_crushes(philo->data);
		pthread_exit(NULL);
	}
	if (pthread_mutex_unlock(philo->left_fork))
		handle_crushes(philo->data);
	if (pthread_mutex_unlock(philo->right_fork))
		handle_crushes(philo->data);
	philo->meals_eaten++;
}

int	search_for_dead_bodies(t_data *data)
{
	int	i;

	i = data->num_philos;
	while (--i >= 0)
	{
		if (philo_get_time() - data->philos[i].last_meal_time  \
		> data->time_to_die)
		{			
			if (pthread_mutex_lock(&data->death_lock))
				handle_crushes(data);
			data->stop = 1;
			if (pthread_mutex_unlock(&data->death_lock))
				handle_crushes(data);
			if (pthread_mutex_lock(&data->print_lock))
				handle_crushes(data);
			printf("%lld %i died\n", philo_get_time() - data->start_time, data->philos[i].id);
			if (pthread_mutex_unlock(&data->print_lock))
				handle_crushes(data);
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

void	threads_waiter(t_data *data)
{
	while (1)
	{
		if (search_for_dead_bodies(data))
			break ;
		if (is_all_satisfied(data))
			break;
	}
}
