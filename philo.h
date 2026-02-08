/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egokce <egokce@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 20:47:56 by egokce            #+#    #+#             */
/*   Updated: 2025/07/18 20:47:56 by egokce           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdint.h>

typedef struct s_philo
{
	int				id;
	int				meals_eaten;
	uint64_t		last_meal_time;
	pthread_t		thread;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	struct s_data	*data;
}	t_philo;

typedef struct s_data
{
	int				num_philos;
	uint64_t		time_to_die;
	uint64_t		time_to_eat;
	uint64_t		time_to_sleep;
	int				num_must_eat;
	int				is_dead;
	int				all_ate;
	uint64_t		start_time;
	int				start_flag;
	int				end_flag;
	pthread_mutex_t	start_mutex;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	meal_mutex;
	pthread_mutex_t	death_mutex;
	t_philo			*philos;
}	t_data;

int			ft_atoi(const char *str);
int			ft_check_arg(int ac, char **av);
void		ft_clean_all(t_data *data);
void		ft_clean_mutex(t_data *data, int i, int fork);
void		ft_clean_thread(t_data *data, int philo);
uint64_t	ft_get_time(void);
void		ft_start_time(t_data *data);
void		ft_usleep(uint64_t duration_ms, t_data *data);
int			ft_init_data(int ac, char **av, t_data *data);
int			ft_init_philo(t_data *data);
int			ft_create_thread(t_data *data);
void		*ft_philo_act(void *arg);
void		*ft_checker_act(void *arg);
int			ft_is_dead(t_data *data);
int			ft_all_ate(t_data *data);
void		ft_print_status(t_philo *philo, char *status);
int			ft_is_start(t_data *data);
void		ft_eat(t_philo *philo);
void		ft_think(t_philo *philo);
void		ft_sleep(t_philo *philo);

#endif