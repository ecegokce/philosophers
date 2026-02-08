/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_act.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egokce <egokce@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 20:47:39 by egokce            #+#    #+#             */
/*   Updated: 2025/07/18 20:47:39 by egokce           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>

static void	ft_single_philo(t_philo *philo)
{
	ft_print_status(philo, "has taken a fork");
	ft_usleep(philo->data->time_to_die, philo->data);
}

static int	ft_end_flag(t_data *data)
{
	int	end_flag;

	pthread_mutex_lock(&data->death_mutex);
	end_flag = data->end_flag;
	pthread_mutex_unlock(&data->death_mutex);
	return (end_flag);
}

static int	ft_philo_ate(t_philo *philo)
{
	int	meals_eaten;
	int	must_eat;

	pthread_mutex_lock(&philo->data->meal_mutex);
	meals_eaten = philo->meals_eaten;
	pthread_mutex_unlock(&philo->data->meal_mutex);
	must_eat = philo->data->num_must_eat;
	if (must_eat != -1 && (must_eat <= meals_eaten))
		return (1);
	return (0);
}

void	*ft_philo_act(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (ft_end_flag(philo->data))
		return (NULL);
	while (ft_is_start(philo->data) == 0)
		usleep(50);
	if (philo->data->num_philos == 1)
	{
		ft_single_philo(philo);
		return (NULL);
	}
	if (philo->id % 2 == 0)
		ft_usleep(philo->data->time_to_eat / 2, philo->data);
	while (!ft_is_dead(philo->data) && !ft_all_ate(philo->data))
	{
		ft_eat(philo);
		if (ft_philo_ate(philo) || ft_is_dead(philo->data))
			break ;
		ft_sleep(philo);
		if (ft_is_dead(philo->data) || ft_all_ate(philo->data))
			break ;
		ft_think(philo);
	}
	return (NULL);
}
