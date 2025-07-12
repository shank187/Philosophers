/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbour <aelbour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 13:23:26 by aelbour           #+#    #+#             */
/*   Updated: 2025/07/12 16:13:32 by aelbour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void died_lonely_philo(t_philo *philo)
{
	int i;

	i = philo->id;
	sem_wait(philo->data->print_lock);
	printf("%lld %i has taken a fork\n", philo_get_time() - philo->data->start_time, philo->id);
	sem_post(philo->data->print_lock);
	ft_usleep(philo->data->time_to_die ,philo);
	clean_resources(philo->data, 1);
	exit(i);
}

int am_i_alive(t_philo *philo)
{
	if (philo_get_time() - philo->last_meal_time  \
	> philo->data->time_to_die && !philo->still_eating)
		return (0);
	return (1);
}

void forks_pickup(t_philo * philo)
{
	if (philo->id == philo->data->num_philos) 
	{
		sem_wait(philo->data->forks);
		safe_printf("has taken a fork", philo);
		sem_wait(philo->data->forks);
		safe_printf("has taken a fork", philo);
		philo->still_eating = 1;
	}
}

void eating_pastaa(t_philo *philo)
{
	safe_printf("is eating", philo);
	if (usleep(philo->data->time_to_eat))
	{
		sem_post(philo->data->forks);
		sem_post(philo->data->forks);
		exit(0);
	}
	sem_post(philo->data->forks);
	sem_post(philo->data->forks);
	philo->last_meal_time = philo_get_time();
	philo->meals_eaten++;
	philo->still_eating = 0;
}

void routine_philo(t_philo *philo)
{
	int i;

	philo->last_meal_time = philo_get_time();
	if (philo->data->num_philos == 1)
		died_lonely_philo(philo);
	while (am_i_alive(philo))
	{
		if(philo->id % 2)
			ft_usleep(100, philo);
		forks_pickup(philo);
		eating_pastaa(philo);
		if (philo->meals_eaten == philo->data->meals_required)
			return (clean_resources(philo->data, 1), exit(0));
		safe_printf("is sleeping", philo);
		ft_usleep(philo->data->time_to_sleep, philo);
		safe_printf("is thinking", philo);
	}
	i = philo->id;
	clean_resources(philo->data, 1);
	exit(i);
}