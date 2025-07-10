/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbour <aelbour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 15:40:43 by aelbour           #+#    #+#             */
/*   Updated: 2025/07/10 11:02:47 by aelbour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
		if (data->stop)
			return (0);
		usleep(100);
	}
	return (1);
}
