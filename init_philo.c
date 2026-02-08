/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egokce <egokce@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 20:47:29 by egokce            #+#    #+#             */
/*   Updated: 2025/07/18 20:47:29 by egokce           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>
#include <stdlib.h>

static void	ft_set_philo(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philos)
	{
		data->philos[i].id = i + 1;
		data->philos[i].meals_eaten = 0;
		data->philos[i].data = data;
		data->philos[i].left_fork = &data->forks[i];
		data->philos[i].right_fork = &data->forks[(i + 1) % data->num_philos];
		i++;
	}
}

static int	ft_init_mutex(t_data *data)
{
	if (pthread_mutex_init(&data->print_mutex, NULL) != 0)
	{
		printf("Error: Could not create print_mutex\n");
		return (1);
	}
	if (pthread_mutex_init(&data->meal_mutex, NULL) != 0)
	{
		printf("Error: Could not create meal_mutex\n");
		ft_clean_mutex(data, 1, 0);
		return (1);
	}
	if (pthread_mutex_init(&data->start_mutex, NULL) != 0)
	{
		printf("Error: Could not create start_mutex\n");
		ft_clean_mutex(data, 2, 0);
		return (1);
	}
	if (pthread_mutex_init(&data->death_mutex, NULL) != 0)
	{
		printf("Error: Could not create death_mutex\n");
		ft_clean_mutex(data, 4, 0);
		return (1);
	}
	return (0);
}

int	ft_init_philo(t_data *data)
{
	int	i;

	data->philos = malloc(sizeof(t_philo) * data->num_philos);
	data->forks = malloc(sizeof(pthread_mutex_t) * data->num_philos);
	if (!data->philos || !data->forks)
	{
		printf("Error: Malloc failed\n");
		ft_clean_mutex(data, 0, 0);
		return (1);
	}
	if (ft_init_mutex(data) != 0)
		return (1);
	i = 0;
	while (i < data->num_philos)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
		{
			printf("Error: Could not create fork mutex\n");
			ft_clean_mutex(data, 4, i);
			return (1);
		}
		i++;
	}
	ft_set_philo(data);
	return (0);
}
