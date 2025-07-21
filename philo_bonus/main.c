/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbour <aelbour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 14:58:34 by aelbour           #+#    #+#             */
/*   Updated: 2025/07/19 10:50:47 by aelbour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	clean_resources(t_data *data, int is_child)
{
	sem_close(data->print_lock);
	sem_close(data->forks);
	if (!is_child)
	{
		sem_unlink("forks");
		sem_unlink("print");
	}
	free(data->philos);
	free(data);
}

int	treat_exits(t_data *data, int status)
{
	int	i;
	int	exit_code;

	exit_code = WEXITSTATUS(status);
	if (exit_code)
	{
		i = -1;
		while (++i < data->num_philos)
			kill(data->philos[i].child_pid, SIGKILL);
		while (waitpid(-1, &status, 0) > 0)
			;
		printf("%lld %i %s\n", philo_get_time() - \
			data->start_time, exit_code, "died");
		return (1);
	}
	return (0);
}

void	restaurant_guard(t_data *data)
{
	int	status;
	int	i;

	while (1)
	{
		if (waitpid(-1, &status, 0) == -1)
		{
			if (errno == EINTR)
			{
				i = -1;
				while (++i < data->num_philos)
					kill(data->philos[i].child_pid, SIGKILL);
				while (waitpid(-1, &status, 0) > 0)
					;
			}
			break ;
		}
		else if (WIFEXITED(status))
			if (treat_exits(data, status))
				break ;
	}
}

int	start_simulation(t_data *data)
{
	int	i;
	int	j;
	int	status;

	i = -1;
	while (++i < data->num_philos)
	{
		data->philos[i].child_pid = fork();
		if (data->philos[i].child_pid == -1)
		{
			j = -1;
			while (++j < i)
				kill(data->philos[j].child_pid, SIGKILL);
			while (waitpid(-1, &status, 0) > 0)
				;
			clean_resources(data, 0);
			sem_unlink("forks");
			sem_unlink("print");
			return (1);
		}
		else if (data->philos[i].child_pid == 0)
			routine_philo(&data->philos[i]);
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_data	*data;

	sem_unlink("forks");
	sem_unlink("print");
	data = malloc(sizeof(t_data));
	if (!data || !parse_init(ac, av, data))
		return (free(data), 1);
	data->start_time = philo_get_time();
	if (start_simulation(data))
		return (write(2, "ERROR !!\n", 9), (1));
	restaurant_guard(data);
	clean_resources(data, 0);
	return (0);
}
