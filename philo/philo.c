/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oumimoun <oumimoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 19:28:40 by oumimoun          #+#    #+#             */
/*   Updated: 2024/03/23 02:09:20 by oumimoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int main(int argc, char **argv)
{
   t_philo *philo;

   if (argc < 5)
   {
      printf("Usage: ./philo <number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> [number_of_times_each_philosopher_must_eat]\n");
      return 1;
   }
   philo = malloc(sizeof(t_philo));
   if (!philo)
   {
      printf("Error: malloc failed\n");
      return 1;
   }
   philo->nb_philo = ft_atoi(argv[1]);
   philo->time_to_die = ft_atoi(argv[2]);
   philo->time_to_eat = ft_atoi(argv[3]);
   philo->time_to_sleep = ft_atoi(argv[4]);
   if (argc == 6)
   {
      philo->nb_must_eat = ft_atoi(argv[5]);
   }

   return 0;
}

