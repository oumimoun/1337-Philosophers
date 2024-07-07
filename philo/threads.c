/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oumimoun <oumimoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 09:07:04 by oumimoun          #+#    #+#             */
/*   Updated: 2024/07/07 15:31:35 by oumimoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_check_flags(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->death_lock);
	if (philo->data->die == 1)
	{
		pthread_mutex_unlock(&philo->data->death_lock);
		return (0);
	}
	pthread_mutex_unlock(&philo->data->death_lock);
	pthread_mutex_lock(&philo->data->full_lock);
	if (philo->data->full == 1)
	{
		pthread_mutex_unlock(&philo->data->full_lock);
		return (0);
	}
	pthread_mutex_unlock(&philo->data->full_lock);
	return (1);
}

void	ft_join_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philos)
	{
		if (pthread_join(data->philos[i].thread, NULL) != 0)
		{
			ft_putstr_fd("Error: thread join failed\n", 2);
			return ;
		}
		i++;
	}
}

int	destroy_mutexes_suite(t_data *data)
{
	if (pthread_mutex_destroy(&data->death_lock) != 0)
	{
		ft_putstr_fd("Error: mutex destroy failed\n", 2);
		return (1);
	}
	if (pthread_mutex_destroy(&data->data_race) != 0)
	{
		ft_putstr_fd("Error: mutex destroy failed\n", 2);
		return (1);
	}
	if (pthread_mutex_destroy(&data->meals_lock) != 0)
	{
		ft_putstr_fd("Error: mutex destroy failed\n", 2);
		return (1);
	}
	if (pthread_mutex_destroy(&data->full_lock) != 0)
	{
		ft_putstr_fd("Error: mutex destroy failed\n", 2);
		return (1);
	}
	return (0);
}

int	destroy_mutexes(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philos)
	{
		if (pthread_mutex_destroy(&data->forks[i]) != 0)
		{
			ft_putstr_fd("Error: mutex destroy failed\n", 2);
			return (1);
		}
		i++;
	}
	if (pthread_mutex_destroy(&data->print) != 0)
	{
		ft_putstr_fd("Error: mutex destroy failed\n", 2);
		return (1);
	}
	if (destroy_mutexes_suite(data))
		return (1);
	return (0);
}
