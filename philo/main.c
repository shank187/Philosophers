/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbour <aelbour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 14:58:34 by aelbour           #+#    #+#             */
/*   Updated: 2025/07/16 16:40:05 by aelbour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	died_lonely_philo(t_philo *philo)
{
	if (pthread_mutex_lock(&philo->data->print_lock))
		philo->data->crash = 1;
	printf("%lld %i has taken a fork\n", philo_get_time() - \
			philo->data->start_time, philo->id);
	if (pthread_mutex_unlock(&philo->data->print_lock))
		philo->data->crash = 1;
}

void	*routine_philo(void *param)
{
	t_philo	*philo;

	philo = (t_philo *) param;
	if (philo->data->num_philos == 1)
	{
		died_lonely_philo(philo);
		return (NULL);
	}
	if (philo->id % 2)
		ft_usleep(1, philo->data);
	while (are_u_alives(philo->data))
	{
		forks_pickup(philo);
		eating_pastaa(philo);
		if (philo->meals_eaten == philo->data->meals_required)
			break ;
		if (are_u_alives(philo->data))
			safe_printf("is sleeping", philo);
		else
			break ;
		if (!ft_usleep(philo->data->time_to_sleep, philo->data))
			break ;
		if (are_u_alives(philo->data))
			safe_printf("is thinking", philo);
		else
			break ;
	}
	return (NULL);
}

void	clean_up_simulation(t_data *data)
{
	int	j;

	usleep(100);
	j = data->crash;
	ft_cleanup_forks(data, data->num_philos);
	pthread_mutex_destroy(&data->death_lock);
	pthread_mutex_destroy(&data->print_lock);
	free(data->forks);
	free(data->philos);
	free(data);
}

// void func(void)
// {
// 	system("leaks philo");
// }

int	main(int ac, char **av)
{
	t_data	*data;
	int		i;

	i = -1;
	data = malloc(sizeof(t_data));
	// atexit(func);
	if (!data || !parse_init(ac, av, data))
		return (free(data), 1);
	data->start_time = philo_get_time();
	while (++i < data->num_philos)
	{
		if (pthread_create(&data->philos[i].thread, \
			NULL, routine_philo, &data->philos[i]))
			return (clean_up_simulation(data), 1);
		else
		{
			pthread_detach(data->philos[i].thread);
			data->philos[i].last_meal_time = philo_get_time();
		}
	}
	ft_usleep(1, data);
	threads_waiter(data);
	i = data->crash;
	clean_up_simulation(data);
	return (i);
}
