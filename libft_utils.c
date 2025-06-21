/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbour <aelbour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 14:38:54 by aelbour           #+#    #+#             */
/*   Updated: 2025/06/20 12:46:29 by aelbour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	ft_get_sign(int *s, long *i, const char *str)
{
	*s = 1;
	if (str[*i] == '-' || str[*i] == '+')
	{
		if (str[*i] == '-')
			*s = -1;
		(*i)++;
	}
}

static void	ft_skip_space(long *i, const char *str)
{
	*i = 0;
	while (str[*i] == 32 || (str[*i] >= 9 && str[*i] <= 13))
		(*i)++;
}

int	ft_atoi(const char *str, int *error)
{
	long	i;
	long	t;
	long	oldt;
	int		s;

	t = 0;
	oldt = 0;
	ft_skip_space(&i, str);
	ft_get_sign(&s, &i, str);
	if(s < 0)
		*error = 1;
	while (str[i] >= '0' && str[i] <= '9')
	{
		t = (t * 10) + (str[i++] - '0');
		if ((t / 10) != oldt && s < 0)
			return (*error = 1, -1);
		else if ((t / 10) != oldt && s > 0)
			return (*error = 1, -1);
		oldt = t;
	}
	if (str[i])
		*error = 1;
	return ((int)t * s);
}
