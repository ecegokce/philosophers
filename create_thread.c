/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_thread.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egokce <egokce@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 20:47:24 by egokce            #+#    #+#             */
/*   Updated: 2025/07/18 20:47:24 by egokce           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>

static void	ft_start_flag(t_data *data)
{
	ft_start_time(data);
	pthread_mutex_lock(&data->start_mutex);
	data->start_flag = 1;
	pthread_mutex_unlock(&data->start_mutex);
}

static int	ft_create_philo_thread(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philos)
	{
		if (pthread_create(&data->philos[i].thread, NULL,
				ft_philo_act, &data->philos[i]) != 0)
		{
			pthread_mutex_lock(&data->death_mutex);
			data->end_flag = 1;
			pthread_mutex_unlock(&data->death_mutex);
			ft_clean_thread(data, i);
			ft_clean_mutex(data, 4, data->num_philos);
			printf("Error: Could not create philosopher thread\n");
			return (1);
		}
		i++;
	}
	return (0);
}

int	ft_create_thread(t_data *data)
{
	int			i;
	pthread_t	checker_thread;

	if (ft_create_philo_thread(data) != 0)
		return (1);
	if (pthread_create(&checker_thread, NULL, ft_checker_act, data) != 0)
	{
		pthread_mutex_lock(&data->death_mutex);
		data->end_flag = 1;
		pthread_mutex_unlock(&data->death_mutex);
		printf("Error creating monitor thread\n");
		ft_clean_thread(data, data->num_philos);
		ft_clean_mutex(data, 4, data->num_philos);
		return (1);
	}
	ft_start_flag(data);
	pthread_join(checker_thread, NULL);
	i = 0;
	while (i < data->num_philos)
	{
		pthread_join(data->philos[i].thread, NULL);
		i++;
	}
	return (0);
}
