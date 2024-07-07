/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oumimoun <oumimoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 14:07:08 by oumimoun          #+#    #+#             */
/*   Updated: 2024/07/07 15:38:14 by oumimoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_one_philo(t_philo *philo)
{
	if (pthread_mutex_lock(&philo->data->data_race) != 0)
		return (ft_putstr_fd("pthread_mutex_lock error", 2), (ERROR));
	if (philo->data->nb_philos == 1)
	{
		if (pthread_mutex_unlock(&philo->data->data_race) != 0)
			return (ft_putstr_fd("pthread_mutex_unlock error", 2), (ERROR));
		if (pthread_mutex_lock(philo->right_fork) != 0)
			return (ft_putstr_fd("pthread_mutex_lock error", 2), (ERROR));
		ft_print(philo, "has taken a fork");
		if (pthread_mutex_unlock(philo->right_fork) != 0)
			return ((ft_putstr_fd("pthread_mutex_unlock error", 2)), (ERROR));
		return (1);
	}
	if (pthread_mutex_unlock(&philo->data->data_race) != 0)
		return (ft_putstr_fd("pthread_mutex_unlock error", 2), (ERROR));
	return (0);
}

int	eat(t_philo *philo)
{
	if (pthread_mutex_lock(philo->right_fork) != 0)
		return (ft_putstr_fd("pthread_mutex_lock error", 2), (ERROR));
	ft_print(philo, "has taken a fork");
	if (pthread_mutex_lock(philo->left_fork) != 0)
		return (ft_putstr_fd("pthread_mutex_lock error", 2), (ERROR));
	ft_print(philo, "has taken a fork");
	ft_print(philo, "is eating");
	ft_usleep(philo->data->time_to_eat, philo);
	if (pthread_mutex_lock(&philo->data->data_race) != 0)
		return (ft_putstr_fd("pthread_mutex_lock error", 2), (ERROR));
	philo->last_time_eating = get_time();
	if (pthread_mutex_unlock(&philo->data->data_race) != 0)
		return (ft_putstr_fd("pthread_mutex_unlock error", 2), (ERROR));
	if (pthread_mutex_lock(&philo->data->meals_lock) != 0)
		return (ft_putstr_fd("pthread_mutex_lock error", 2), (ERROR));
	philo->meals++;
	if (pthread_mutex_unlock(&philo->data->meals_lock) != 0)
		return (ft_putstr_fd("pthread_mutex_unlock error", 2), (ERROR));
	if (pthread_mutex_unlock(philo->right_fork) != 0)
		return (ft_putstr_fd("pthread_mutex_unlock error", 2), (ERROR));
	if (pthread_mutex_unlock(philo->left_fork) != 0)
		return (ft_putstr_fd("pthread_mutex_unlock error", 2), (ERROR));
	return (SUCCESS);
}

void	*ft_philo(void *philos)
{
	t_philo	*philo;

	philo = (t_philo *)(philos);
	if (philo->id % 2 == 0)
		ft_usleep(philo->data->time_to_eat, philo);
	while (ft_check_flags(philo))
	{
		if (ft_one_philo(philo))
			return (NULL);
		if (eat(philo) == ERROR)
			return (NULL);
		ft_print(philo, "is sleeping");
		ft_usleep(philo->data->time_to_sleep, philo);
		ft_print(philo, "is thinking");
	}
	return (NULL);
}
