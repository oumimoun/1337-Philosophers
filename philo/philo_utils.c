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
	int		signe;
	long	total;

	signe = 1;
	total = 0;
	i = 0;
	while (str[i] == ' ')
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			signe *= (-1);
		if (str[++i] == '+' || str[i] == '-' || str[i] == '\0')
			return (-1);
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		total = total * 10 + str[i] - '0';
		if (str[++i] == '+' || str[i] == '-')
			return (-1);
	}
	if ((total * signe) < INT_MIN || (total * signe) > INT_MAX)
		return (-1);
	return ((int)(signe * total));
}

void	ft_usleep(size_t time)
{
	size_t			d_time;
	struct timeval	tp;

	gettimeofday(&tp, NULL);
	d_time = (size_t)(tp.tv_sec * 1000) + (size_t)(tp.tv_usec / 1000);
	usleep((time - 20) * 1000);
	time += d_time;
	while (d_time < time)
	{
		gettimeofday(&tp, NULL);
		d_time = (size_t)(tp.tv_sec * 1000) + (size_t)(tp.tv_usec / 1000);
	}
}

size_t get_time(void)
{
   struct timeval time;

   if (gettimeofday(&time, NULL) == -1)
      ft_putstr_fd("gettimeofday() error\n", 2);
   return ((size_t)(time.tv_sec * 1000 + time.tv_usec / 1000));
}

int ft_print(t_philo *philo, char *str)
{
   size_t time;

   if (ft_check_flags(philo))
   {
      pthread_mutex_lock(&philo->data->print);
      time = get_time() - philo->data->start_time;
      printf("%zu %d %s\n", time, philo->id, str);
      pthread_mutex_unlock(&philo->data->print);
   }
   return (0);
}

void ft_putstr_fd(char *s, int fd)
{
   int i;

   if (!s || fd < 0)
      return;
   i = 0;
   while (s[i])
   {
      write(fd, &s[i], 1);
      i++;
   }
}
