/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oumimoun <oumimoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 00:53:53 by oumimoun          #+#    #+#             */
/*   Updated: 2024/03/20 22:50:38 by oumimoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(char *str)
{
	int		i;
	long	total;

	total = 0;
	i = 0;
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	if (str[i] == '-')
		return (-1);
	else if (str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		if ((total) > INT_MAX)
			return (-1);
		total = total * 10 + str[i] - '0';
		i++;
	}
	if (str[i])
		return (-1);
	return ((int)(total));
}

void	ft_usleep(size_t milliseconds, t_philo *philo)
{
	size_t	start;

	start = get_time();
	while ((get_time() - start) < milliseconds)
	{
		if (ft_check_flags(philo) == 0)
			return ;
		usleep(500);
	}
}

size_t	get_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		ft_putstr_fd("gettimeofday() error\n", 2);
	return ((size_t)(time.tv_sec * 1000 + time.tv_usec / 1000));
}

int	ft_print(t_philo *philo, char *str)
{
	size_t	time;

	if (ft_check_flags(philo))
	{
		if (pthread_mutex_lock(&philo->data->print) != 0)
			return (ft_putstr_fd("pthread_mutex_lock error", 2), ERROR);
		time = get_time() - philo->data->start_time;
		printf("%zu %d %s\n", time, philo->id, str);
		if (pthread_mutex_unlock(&philo->data->print) != 0)
			return (ft_putstr_fd("pthread_mutex_unlock error", 2), ERROR);
	}
	return (SUCCESS);
}

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	if (!s || fd < 0)
		return ;
	i = 0;
	while (s[i])
	{
		write(fd, &s[i], 1);
		i++;
	}
}
