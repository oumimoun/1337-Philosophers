/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oumimoun <oumimoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 19:28:40 by oumimoun          #+#    #+#             */
/*   Updated: 2024/03/20 22:54:43 by oumimoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_init_mutexes_suite(t_data *data)
{
	if (pthread_mutex_init(&data->print, NULL) != 0)
	{
		ft_putstr_fd("Error: mutex init failed\n", 2);
		return ;
	}
	if (pthread_mutex_init(&data->death_lock, NULL) != 0)
	{
		ft_putstr_fd("Error: mutex init failed\n", 2);
		return ;
	}
	if (pthread_mutex_init(&data->data_race, NULL) != 0)
	{
		ft_putstr_fd("Error: mutex init failed\n", 2);
		return ;
	}
	if (pthread_mutex_init(&data->meals_lock, NULL) != 0)
	{
		ft_putstr_fd("Error: mutex init failed\n", 2);
		return ;
	}
	if (pthread_mutex_init(&data->full_lock, NULL) != 0)
	{
		ft_putstr_fd("Error: mutex init failed\n", 2);
		return ;
	}
}

void	ft_init_mutexes(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philos)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
		{
			ft_putstr_fd("Error: mutex init failed\n", 2);
			return ;
		}
		i++;
	}
	ft_init_mutexes_suite(data);
}

int	ft_init_data(t_data *data)
{
	data->philos = malloc(sizeof(t_philo) * data->nb_philos);
	if (data->philos == NULL)
	{
		ft_putstr_fd("Error: malloc failed\n", 2);
		return (1);
	}
	data->forks = malloc(sizeof(pthread_mutex_t) * data->nb_philos);
	if (data->forks == NULL)
	{
		ft_putstr_fd("Error: malloc failed\n", 2);
		return ((free(data->philos)), (data->philos = NULL), (1));
	}
	data->start_time = 0;
	ft_init_mutexes(data);
	return (0);
}

int	ft_create_monitor(t_data *data)
{
	pthread_t	monitor;

	monitor = NULL;
	if (pthread_create(&monitor, NULL, ft_monitor, data->philos) != 0)
		return (ft_putstr_fd("Error: thread creation failed\n", 2), (1));
	if (pthread_join(monitor, NULL) != 0)
		return (ft_putstr_fd("Error: thread join failed\n", 2), (1));
	ft_join_threads(data);
	return (0);
}

int	ft_init_philos(t_data *data)
{
	int	i;

	i = 0;
	data->start_time = get_time();
	while (i < data->nb_philos)
	{
		data->philos[i].id = i + 1;
		data->philos[i].data = data;
		data->philos[i].meals = 0;
		data->philos[i].last_time_eating = get_time();
		data->philos[i].right_fork = &(data->forks[i]);
		if (i == 0)
			data->philos[i].left_fork = &(data->forks[data->nb_philos - 1]);
		else
			data->philos[i].left_fork = &(data->forks[i - 1]);
		if (pthread_create(&data->philos[i].thread, NULL, \
			ft_philo, &data->philos[i]) != 0)
			return (ft_putstr_fd("Error: thread creation failed\n", 2), (1));
		i++;
	}
	if (ft_create_monitor(data))
		return (1);
	return (0);
}
