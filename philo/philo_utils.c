/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbour <aelbour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 15:40:43 by aelbour           #+#    #+#             */
/*   Updated: 2025/07/13 11:25:06 by aelbour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void handle_crushes(t_data *data)
{
	free(data->forks);
	free(data->philos);
	free(data);
	write(2, "A FUNCTION FAILED !!\n", 2);
	exit(1);
}

int safe_printf(char *str, t_philo *philo)
{
	if(are_u_alives(philo->data))
	{
		if (pthread_mutex_lock(&philo->data->print_lock))
			handle_crushes(philo->data);
		printf("%lld %i %s\n", philo_get_time() - philo->data->start_time, philo->id, str);
		if (pthread_mutex_unlock(&philo->data->print_lock))
			handle_crushes(philo->data);
		return (1);
	}	
	return (0);
}

int are_u_alives(t_data *data)
{
	pthread_mutex_lock(&data->death_lock);
	if(!data->stop)
	{
		if (pthread_mutex_unlock(&data->death_lock))
			handle_crushes(data);
		return (1);
	}
	else
	{
		if (pthread_mutex_unlock(&data->death_lock))
			handle_crushes(data);
		return (0);
	}
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
		if (usleep(1000))
			handle_crushes(data);
	}
	return (1);
}
