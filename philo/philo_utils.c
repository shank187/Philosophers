/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbour <aelbour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 15:40:43 by aelbour           #+#    #+#             */
/*   Updated: 2025/07/11 12:53:42 by aelbour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int safe_printf(char *str, t_philo *philo)
{
	if(are_u_alives(philo->data))
	{
		pthread_mutex_lock(&philo->data->print_lock);
		printf("%lld %i %s\n", philo_get_time() - philo->data->start_time, philo->id, str);
		pthread_mutex_unlock(&philo->data->print_lock);
		return (1);
	}	
	return (0);
}

int are_u_alives(t_data *data)
{
	pthread_mutex_lock(&data->death_lock);
	if(!data->stop)
		return (pthread_mutex_unlock(&data->death_lock), 1);
	else
		return (pthread_mutex_unlock(&data->death_lock), 0);
}

long long philo_get_time()
{
	struct timeval tv;
	long long ms_time;

	if (gettimeofday(&tv, NULL) == -1)
		return (-1);
	ms_time = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	return (ms_time);
}

int	ft_usleep(size_t milliseconds, t_data *data)
{
	size_t	start;

	start = philo_get_time();
	while ((philo_get_time() - start) < milliseconds)
	{
		if (!are_u_alives(data))
			return (0);
		usleep(100	);
	}
	return (1);
}
