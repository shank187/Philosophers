/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbour <aelbour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 15:40:43 by aelbour           #+#    #+#             */
/*   Updated: 2025/07/12 16:12:59 by aelbour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void safe_printf(char *str, t_philo *philo)
{
	sem_wait(philo->data->print_lock);
	printf("%lld %i %s\n", philo_get_time() - philo->data->start_time, philo->id, str);
	sem_post(philo->data->print_lock);
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

void	ft_usleep(size_t millisecond, t_philo *philo)
{
	size_t	start;
	int i;

	i =  philo->id;
	start = philo_get_time();
	while ((philo_get_time() - start) < millisecond)
	{
		if (usleep(5) || !am_i_alive(philo))
			return (clean_resources(philo->data, 1), fprintf(stderr,"the philo returned id is %i\n", i), exit(i));
	}
}
