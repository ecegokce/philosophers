/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egokce <egokce@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 20:47:59 by egokce            #+#    #+#             */
/*   Updated: 2025/07/18 20:47:59 by egokce           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>
#include <sys/time.h>

uint64_t	ft_get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((uint64_t)(tv.tv_sec * 1000 + tv.tv_usec / 1000));
}

void	ft_start_time(t_data *data)
{
	uint64_t	now;
	int			j;

	data->start_time = ft_get_time();
	now = data->start_time;
	pthread_mutex_lock(&data->meal_mutex);
	j = 0;
	while (j < data->num_philos)
	{
		data->philos[j].last_meal_time = now;
		j++;
	}
	pthread_mutex_unlock(&data->meal_mutex);
}

void	ft_usleep(uint64_t duration_ms, t_data *data)
{
	uint64_t	start;
	uint64_t	now;

	start = ft_get_time();
	while (!ft_is_dead(data))
	{
		now = ft_get_time();
		if (now - start >= duration_ms)
			break ;
		usleep(50);
	}
}
