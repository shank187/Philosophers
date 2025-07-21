/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbour <aelbour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 15:40:43 by aelbour           #+#    #+#             */
/*   Updated: 2025/07/19 10:05:11 by aelbour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	am_i_alive(t_philo *philo)
{
	if (philo_get_time() - philo->last_meal_time \
	> philo->data->time_to_die)
		return (0);
	return (1);
}

void	handle_crushes(t_data *data, int is_child)
{
	if (!is_child)
	{
		sem_unlink("forks");
		sem_unlink("print");
	}
	free(data->forks);
	free(data->philos);
	free(data);
	write(2, "A FUNCTION FAILED !!\n", 21);
	exit(!is_child);
}

void	safe_printf(char *str, t_philo *philo)
{
	if (sem_wait(philo->data->print_lock))
		handle_crushes(philo->data, 1);
	printf("%lld %i %s\n", philo_get_time() - \
		philo->data->start_time, philo->id, str);
	if (sem_post(philo->data->print_lock))
		handle_crushes(philo->data, 1);
}

long long	philo_get_time(void)
{
	struct timeval	tv;
	long long		ms_time;

	if (gettimeofday(&tv, NULL) == -1)
		return (-1);
	ms_time = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	return (ms_time);
}

void	ft_usleep(size_t millisecond, t_philo *philo)
{
	size_t	start;
	int		i;

	i = philo->id;
	start = philo_get_time();
	while ((philo_get_time() - start) < millisecond)
	{
		if (!am_i_alive(philo))
		{
			clean_resources(philo->data, 1);
			exit(0);
		}
		if (usleep(100))
			handle_crushes(philo->data, 1);
	}
}
