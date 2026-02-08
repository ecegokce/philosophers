/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egokce <egokce@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 20:47:46 by egokce            #+#    #+#             */
/*   Updated: 2025/07/18 20:47:46 by egokce           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>

int	ft_is_dead(t_data *data)
{
	int	dead;

	pthread_mutex_lock(&data->death_mutex);
	dead = data->is_dead;
	pthread_mutex_unlock(&data->death_mutex);
	return (dead);
}

int	ft_all_ate(t_data *data)
{
	int	ate;

	pthread_mutex_lock(&data->death_mutex);
	ate = data->all_ate;
	pthread_mutex_unlock(&data->death_mutex);
	return (ate);
}

void	ft_print_status(t_philo *philo, char *status)
{
	uint64_t	current_time;

	pthread_mutex_lock(&philo->data->print_mutex);
	if (!ft_is_dead(philo->data) && !ft_all_ate(philo->data))
	{
		current_time = ft_get_time() - philo->data->start_time;
		printf("%lu %d %s\n", current_time, philo->id, status);
	}
	pthread_mutex_unlock(&philo->data->print_mutex);
}

int	ft_is_start(t_data *data)
{
	int	start;

	pthread_mutex_lock(&data->start_mutex);
	start = data->start_flag;
	pthread_mutex_unlock(&data->start_mutex);
	return (start);
}
