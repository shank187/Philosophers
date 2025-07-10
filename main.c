/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbour <aelbour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 14:58:34 by aelbour           #+#    #+#             */
/*   Updated: 2025/07/10 11:28:39 by aelbour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void *routine_philo(void *param)
{
	t_philo *philo = (t_philo*)param;

	philo->last_meal_time = philo_get_time();
	while (!philo->data->stop)
	{
		if (philo->id == philo->data->num_philos) 
		{
			pthread_mutex_lock(philo->right_fork);
			pthread_mutex_lock(&philo->data->print_lock);
			printf("%lld %i has taken a fork\n", philo_get_time() - philo->data->start_time, philo->id);
			pthread_mutex_unlock(&philo->data->print_lock);
			pthread_mutex_lock(philo->left_fork);
			pthread_mutex_lock(&philo->data->print_lock);
			printf("%lld %i has taken a fork\n", philo_get_time() - philo->data->start_time, philo->id);
			pthread_mutex_unlock(&philo->data->print_lock);
		}
		else
		{
			pthread_mutex_lock(philo->left_fork);
			pthread_mutex_lock(&philo->data->print_lock);
			printf("%lld %i has taken a fork\n", philo_get_time() - philo->data->start_time, philo->id);
			pthread_mutex_unlock(&philo->data->print_lock);
			pthread_mutex_lock(philo->right_fork);
			pthread_mutex_lock(&philo->data->print_lock);
			printf("%lld %i has taken a fork\n", philo_get_time() - philo->data->start_time, philo->id);
			pthread_mutex_unlock(&philo->data->print_lock);			
		}
		pthread_mutex_lock(&philo->data->print_lock);
		printf("%lld %i is eating\n",  philo_get_time() - philo->data->start_time, philo->id);
		pthread_mutex_unlock(&philo->data->print_lock);
		if(!ft_usleep(philo->data->time_to_eat, philo->data))
		{
			pthread_mutex_unlock(philo->right_fork);
			pthread_mutex_unlock(philo->left_fork);
			pthread_exit(NULL);
		}
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		philo->meals_eaten++;
		philo->last_meal_time = philo_get_time();
		if(philo->meals_eaten == philo->data->meals_required)
			pthread_exit(NULL);
		pthread_mutex_lock(&philo->data->print_lock);
		printf("%lld %i is sleeping\n",  philo_get_time() - philo->data->start_time, philo->id);
		pthread_mutex_unlock(&philo->data->print_lock);
		if(!ft_usleep(philo->data->time_to_sleep, philo->data))
			pthread_exit(NULL);
		pthread_mutex_lock(&philo->data->print_lock);
		printf("%lld %i is thinking\n",  philo_get_time() - philo->data->start_time, philo->id);
		pthread_mutex_unlock(&philo->data->print_lock);
	}
	pthread_exit(NULL);
	return (NULL);
}


int main(int ac, char **av)
{
	t_data *data;
	int i;

	i = -1;
	data = malloc(sizeof(t_data));
	if (!data || !parse_init(ac, av, data))
		return(1);
	printf("passed parsing\n");
	data->start_time = philo_get_time();
	while (++i < data->num_philos)
		pthread_create(&data->philos[i].thread, NULL, routine_philo,  &data->philos[i]);
	while (1)// monitor loop that first check for corpse if not it checks if the meals reuired is provided to check if they all has eaten their meals number
	{
		ft_usleep(100, data);
		i = -1;
		while (++i < data->num_philos)
		{
			if (philo_get_time() - data->philos[i].last_meal_time  \
				> data->time_to_die)
			{
				pthread_mutex_lock(&data->print_lock);
				data->stop = 1;
				printf("%lld %i died\n", philo_get_time() - data->start_time, data->philos[i].id);
				pthread_mutex_unlock(&data->print_lock);
				break ;
			}
		}
		if(data->stop)
			break;
		if (data->meals_required != 0)
		{
			i = -1;
			while (++i < data->num_philos && data->philos[i].meals_eaten >= data->meals_required);
			if (i == data->num_philos)
			{
				data->stop = 1;
				break ;
			}
		}
	}
	i = -1;
	while (++i < data->num_philos)
		pthread_join(data->philos[i].thread, NULL);
}
