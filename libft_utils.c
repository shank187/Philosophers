/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbour <aelbour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 14:38:54 by aelbour           #+#    #+#             */
/*   Updated: 2025/07/09 16:59:49 by aelbour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *str, int *error)
{
	long	i;
	long	t;
	long	oldt;

	t = 0;
	i = 0;
	oldt = 0;
	if(!str[0])
		return (*error = 1, 0);
	while (str[i] >= '0' && str[i] <= '9')
	{
		t = (t * 10) + (str[i++] - '0');
		if ((t / 10) != oldt)
			return (*error = 1, -1);
		oldt = t;
	}
	if (str[i])
		*error = 1;
	return ((int)t);
}
