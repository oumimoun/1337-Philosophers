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

int number_of_philosophers;
int time_to_die;
int time_to_eat;
int time_to_sleep;
int number_of_times_each_philosopher_must_eat;



void *philosopher(void *arg)
{
   int philosopher_number = *(int *)arg;
   int left_fork = philosopher_number;
   int right_fork = (philosopher_number + 1) % number_of_philosophers;

   while (1)
   {
      // Think
      printf("%ld %d is thinking\n", time(NULL), philosopher_number + 1);
      usleep(1000);

      // Try to take forks
      pthread_mutex_lock(&forks[left_fork]);
      pthread_mutex_lock(&forks[right_fork]);

      // Eat
      printf("%ld %d has taken a fork\n", time(NULL), philosopher_number + 1);
      printf("%ld %d is eating\n", time(NULL), philosopher_number + 1);
      usleep(time_to_eat * 1000);

      // Put down forks
      printf("%ld %d is putting down a fork\n", time(NULL), philosopher_number + 1);
      pthread_mutex_unlock(&forks[left_fork]);
      pthread_mutex_unlock(&forks[right_fork]);

      // Sleep
      printf("%ld %d is sleeping\n", time(NULL), philosopher_number + 1);
      usleep(time_to_sleep * 1000);
   }
}

int main(int argc, char **argv)
{
   t_philo *philo;

   if (argc < 5)
   {
      printf("Usage: %s <number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> [number_of_times_each_philosopher_must_eat]\n", argv[0]);
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

   // Initialize forks
   for (int i = 0; i < number_of_philosophers; i++)
   {
      pthread_mutex_init(&forks[i], NULL);
   }

   pthread_t philosophers[number_of_philosophers];
   int philosopher_numbers[number_of_philosophers];

   // Create philosopher threads
   for (int i = 0; i < number_of_philosophers; i++)
   {
      philosopher_numbers[i] = i;
      pthread_create(&philosophers[i], NULL, philosopher, &philosopher_numbers[i]);
   }

   // Wait for all philosophers to finish
   for (int i = 0; i < number_of_philosophers; i++)
   {
      pthread_join(philosophers[i], NULL);
   }

   // Cleanup
   for (int i = 0; i < number_of_philosophers; i++)
   {
      pthread_mutex_destroy(&forks[i]);
   }

   return 0;
}

