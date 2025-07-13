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
	> philo->data->time_to_die)
		return (0);
	return (1);
}

void forks_pickup(t_philo * philo)
{
	sem_wait(philo->data->forks);
	safe_printf("has taken a fork", philo);
	sem_wait(philo->data->forks);
	safe_printf("has taken a fork", philo);
}

void eating_pastaa(t_philo *philo)
{
	safe_printf("is eating", philo);
	philo->last_meal_time = philo_get_time();
	ft_usleep(philo->data->time_to_eat, philo);
	sem_post(philo->data->forks);
	sem_post(philo->data->forks);
	philo->meals_eaten++;
}


// void *ft_ripper(void *param)
// {
// 	t_philo *philo;

// 	philo = (t_philo*) param;
// 	while(1)
// 	{
// 		if(philo_get_time() - philo->last_meal_time > philo->data->time_to_die)
// 		{
// 			clean_resources(philo->data, 1);
// 			fprintf(stderr, "\n==================================================");
// 			fprintf(stderr, "==================================================\n");
// 			exit(philo->id);
// 		}
// 		usleep(50);
// 	}
// 	return (NULL);
// }
void routine_philo(t_philo *philo)
{
	int i;
	// pthread_t ripper;
	// pthread_create(&ripper, NULL, &ft_ripper, philo);

	if (philo->data->num_philos == 1)
		died_lonely_philo(philo);
	philo->last_meal_time = philo_get_time();
	while (am_i_alive(philo))
	{
		if(philo->id % 2)
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