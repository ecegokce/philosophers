/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egokce <egokce@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 20:47:20 by egokce            #+#    #+#             */
/*   Updated: 2025/07/18 20:47:20 by egokce           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>
#include <unistd.h>

static int	ft_philo_died(t_data *data, int i, uint64_t current_time)
{
	pthread_mutex_lock(&data->death_mutex);
	data->is_dead = 1;
	pthread_mutex_unlock(&data->death_mutex);
	pthread_mutex_lock(&data->print_mutex);
	printf("%lu %d died\n", current_time - data->start_time,
		data->philos[i].id);
	pthread_mutex_unlock(&data->print_mutex);
	return (1);
}

static int	ft_check_death(t_data *data)
{
	int			i;
	uint64_t	current_time;
	uint64_t	last_meal;

	i = 0;
	while (i < data->num_philos)
	{
		pthread_mutex_lock(&data->meal_mutex);
		current_time = ft_get_time();
		last_meal = data->philos[i].last_meal_time;
		pthread_mutex_unlock(&data->meal_mutex);
		if (current_time - last_meal > data->time_to_die)
			return (ft_philo_died(data, i, current_time));
		i++;
	}
	return (0);
}

static int	ft_check_all_ate(t_data *data)
{
	int	i;
	int	ready_philos;

	if (data->num_must_eat == -1)
		return (0);
	ready_philos = 0;
	pthread_mutex_lock(&data->meal_mutex);
	i = 0;
	while (i < data->num_philos)
	{
		if (data->philos[i].meals_eaten >= data->num_must_eat)
			ready_philos++;
		i++;
	}
	pthread_mutex_unlock(&data->meal_mutex);
	if (ready_philos >= data->num_philos)
	{
		pthread_mutex_lock(&data->death_mutex);
		data->all_ate = 1;
		pthread_mutex_unlock(&data->death_mutex);
		return (1);
	}
	return (0);
}

void	*ft_checker_act(void *arg)
{
	t_data	*data;

	data = (t_data *)arg;
	while (ft_is_start(data) == 0)
		usleep(50);
	while (1)
	{
		if (ft_check_death(data))
			break ;
		if (ft_check_all_ate(data))
			break ;
	}
	return (NULL);
}
