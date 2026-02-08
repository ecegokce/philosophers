/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egokce <egokce@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 20:47:32 by egokce            #+#    #+#             */
/*   Updated: 2025/07/18 20:47:32 by egokce           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_data	data;

	if (ft_check_arg(ac, av) != 0)
		return (1);
	if (ft_init_data(ac, av, &data) != 0)
		return (0);
	if (ft_init_philo(&data) != 0)
		return (1);
	if (ft_create_thread(&data) != 0)
		return (1);
	ft_clean_all(&data);
	return (0);
}
