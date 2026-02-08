/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egokce <egokce@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 20:48:03 by egokce            #+#    #+#             */
/*   Updated: 2025/07/24 13:01:39 by egokce           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdlib.h>

void	ft_clean_all(t_data *data)
{
	int	i;

	i = 0;
	if (data->forks)
	{
		while (i < data->num_philos)
		{
			pthread_mutex_destroy(&data->forks[i]);
			i++;
		}
		free(data->forks);
	}
	pthread_mutex_destroy(&data->print_mutex);
	pthread_mutex_destroy(&data->meal_mutex);
	pthread_mutex_destroy(&data->start_mutex);
	pthread_mutex_destroy(&data->death_mutex);
	if (data->philos)
		free(data->philos);
}

void	ft_clean_thread(t_data *data, int philo)
{
	int	i;

	i = 0;
	while (i < philo)
	{
		pthread_join(data->philos[i].thread, NULL);
		i++;
	}
}

static void	ft_clean_forks(t_data *data, int fork)
{
	int	i;

	i = 0;
	while (i < fork)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
}

void	ft_clean_mutex(t_data *data, int i, int fork)
{
	if (i >= 1)
		pthread_mutex_destroy(&data->print_mutex);
	if (i >= 2)
		pthread_mutex_destroy(&data->meal_mutex);
	if (i >= 3)
		pthread_mutex_destroy(&data->start_mutex);
	if (i >= 4)
		pthread_mutex_destroy(&data->death_mutex);
	if (fork > 0)
		ft_clean_forks(data, fork);
	if (data->philos)
		free(data->philos);
	if (data->forks)
		free(data->forks);
}
