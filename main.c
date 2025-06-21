/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbour <aelbour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 14:58:34 by aelbour           #+#    #+#             */
/*   Updated: 2025/06/21 16:08:11 by aelbour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int roll_weel(t_data *data)
{
	pthread_mutex_unlock(&data->death_lock);
	if(data->someone_died)
		return (0);
	else
		return (1);
	pthread_mutex_lock(&data->death_lock);
}

void *routine_philo(void *param)
{
	t_data *data = (t_data*)param;
	while(roll_weel(data))
	{
		
	}
}


int main(int ac, char **av)
{
	t_data *data;
	int i;

	i = -1;
	data = malloc(sizeof(t_data));
	if (!parse_init(ac, av, data))
		return(1);
	while(++i < data->num_philos)
		pthread_create(data->philos[i].thread, NULL, routine_philo, data);
	while(1)// monitor loop that first check for corpse if not it checks if the meals reuired is provided to check if they all has eaten their meals number
	{
		i = -1;
		while (++i < data->num_philos)
		{
			if(data->philos[i].last_meal_time - philo_get_time() \
				> data->time_to_die)
			{
				pthread_mutex_lock(&data->death_lock);
				data->someone_died = 1;
				pthread_mutex_unlock(&data->death_lock);
				pthread_mutex_lock(&data->print_lock);
				printf("%ld %i died", philo_get_time(), data->philos->id);
				pthread_mutex_unlock(&data->print_lock);
				break;
			}
		}
		i = -1;
		if(data->meals_required > 0)
		{
			while (++i < data->num_philos && data->philos[i].meals_eaten >= data->meals_required);
			if(i == data->num_philos)
			{
				pthread_mutex_unlock(&data->death_lock);
				data->someone_died = 1;
				pthread_mutex_lock(&data->death_lock);
			}
		}
		usleep(1000);
	}
	i = -1;
	while (++i < data->num_philos)
		pthread_join(data->philos[i].thread, NULL);
	
}
