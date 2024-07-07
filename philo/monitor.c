/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oumimoun <oumimoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 15:12:48 by oumimoun          #+#    #+#             */
/*   Updated: 2024/07/07 15:21:55 by oumimoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_check_last_time_eating(t_philo *philo, int i)
{
	pthread_mutex_lock(&philo->data->data_race);
	if ((get_time() - philo[i].last_time_eating) >= philo->data->time_to_die)
	{
		pthread_mutex_unlock(&philo->data->data_race);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->data_race);
	return (0);
}

int	ft_check_death(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->data->nb_philos)
	{
		if (ft_check_last_time_eating(philo, i))
		{
			ft_print(philo, "died");
			pthread_mutex_lock(&philo->data->death_lock);
			philo->data->die = 1;
			pthread_mutex_unlock(&philo->data->death_lock);
			return (0);
		}
		i++;
	}
	return (1);
}

int	ft_check_full(t_philo *philo)
{
	int	i;
	int	countmeals;

	i = 0;
	countmeals = 0;
	while (i < philo->data->nb_philos)
	{
		pthread_mutex_lock(&philo->data->meals_lock);
		if (philo->data->nb_must_eat != -1 \
			&& philo[i].meals >= philo->data->nb_must_eat)
			countmeals++;
		if (countmeals == philo->data->nb_philos)
		{
			pthread_mutex_unlock(&philo->data->meals_lock);
			pthread_mutex_lock(&philo->data->full_lock);
			philo->data->full = 1;
			pthread_mutex_unlock(&philo->data->full_lock);
			return (0);
		}
		pthread_mutex_unlock(&philo->data->meals_lock);
		i++;
	}
	return (1);
}

void	*ft_monitor(void *philos)
{
	t_philo	*philo;

	philo = (t_philo *)philos;
	while (1)
	{
		if (ft_check_death(philo) == 0)
			return (NULL);
		if (ft_check_full(philo) == 0)
			return (NULL);
	}
	return (NULL);
}
