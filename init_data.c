/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egokce <egokce@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 20:47:27 by egokce            #+#    #+#             */
/*   Updated: 2025/07/18 20:47:27 by egokce           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_init_data(int ac, char **av, t_data *data)
{
	data->num_philos = ft_atoi(av[1]);
	if (data->num_philos == 0)
		return (1);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	data->is_dead = 0;
	data->all_ate = 0;
	data->start_time = 0;
	data->start_flag = 0;
	data->end_flag = 0;
	if (ac == 6)
		data->num_must_eat = ft_atoi(av[5]);
	else
		data->num_must_eat = -1;
	return (0);
}
