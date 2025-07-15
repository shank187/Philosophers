/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbour <aelbour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 13:23:26 by aelbour           #+#    #+#             */
/*   Updated: 2025/07/13 11:27:26 by aelbour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	died_lonely_philo(t_philo *philo)
{
	int	i;

	i = philo->id;
	if (sem_wait(philo->data->print_lock))
		handle_crushes(philo->data, 1);
	printf("%lld %i has taken a fork\n", philo_get_time() - \
		philo->data->start_time, philo->id);
	ft_usleep(philo->data->time_to_die, philo);
	if (sem_post(philo->data->print_lock))
		handle_crushes(philo->data, 1);
	clean_resources(philo->data, 1);
	exit(i);
}

int	am_i_alive(t_philo *philo)
{
	if (philo_get_time() - philo->last_meal_time \
	> philo->data->time_to_die)
		return (0);
	return (1);
}

void	forks_pickup(t_philo *philo)
{
	if (sem_wait(philo->data->forks))
		handle_crushes(philo->data, 1);
	safe_printf("has taken a fork", philo);
	if (sem_wait(philo->data->forks))
		handle_crushes(philo->data, 1);
	safe_printf("has taken a fork", philo);
}

void	eating_pastaa(t_philo *philo)
{
	safe_printf("is eating", philo);
	philo->last_meal_time = philo_get_time();
	ft_usleep(philo->data->time_to_eat, philo);
	if (sem_post(philo->data->forks))
		handle_crushes(philo->data, 1);
	if (sem_post(philo->data->forks))
		handle_crushes(philo->data, 1);
	philo->meals_eaten++;
}

void	routine_philo(t_philo *philo)
{
	int	i;

	philo->last_meal_time = philo_get_time();
	if (philo->data->num_philos == 1)
		died_lonely_philo(philo);
	while (am_i_alive(philo))
	{
		if (philo->id % 2)
			ft_usleep(1, philo);
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
