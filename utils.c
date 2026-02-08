/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egokce <egokce@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 20:48:03 by egokce            #+#    #+#             */
/*   Updated: 2025/07/18 20:48:03 by egokce           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>

int	ft_atoi(const char *nptr)
{
	int	i;
	int	sign;
	int	result;

	result = 0;
	i = 0;
	sign = 1;
	while ((9 <= nptr[i] && nptr[i] <= 13) || nptr[i] == ' ')
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			sign = -1;
		i++;
	}
	while ('0' <= nptr[i] && nptr[i] <= '9')
	{
		result = result * 10 + (nptr[i] - '0');
		i++;
	}
	return (result * sign);
}

static int	ft_check_usage(int ac)
{
	if (ac != 5 && ac != 6)
	{
		printf("Usage: ./philo [number_of_philosophers] ");
		printf("[time_to_die] [time_to_eat] [time_to_sleep]");
		printf("(optional)[number_of_times_each_philosopher_must_eat]\n");
		return (1);
	}
	return (0);
}

int	ft_check_arg(int ac, char **av)
{
	int	i;
	int	j;

	if (ft_check_usage(ac) != 0)
		return (1);
	i = 1;
	while (i < ac)
	{
		j = 0;
		while (av[i][j])
		{
			if (av[i][j] < '0' || av[i][j] > '9')
			{
				printf("Error: Incorrect arguments");
				return (1);
			}
			else
				j++;
		}
		i++;
	}
	return (0);
}
