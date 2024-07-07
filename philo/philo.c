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

int ft_check_flags(t_philo *philo)
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

void ft_init_mutexes(t_data *data)
{
   int i;

   i = 0;
   while (i < data->nb_philos)
   {
      if (pthread_mutex_init(&data->forks[i], NULL) != 0)
      {
         ft_putstr_fd("Error: mutex init failed\n", 2);
         return;
      }
      i++;
   }
   if (pthread_mutex_init(&data->print, NULL) != 0)
   {
      ft_putstr_fd("Error: mutex init failed\n", 2);
      return;
   }
   if (pthread_mutex_init(&data->death_lock, NULL) != 0)
   {
      ft_putstr_fd("Error: mutex init failed\n", 2);
      return;
   }
   if (pthread_mutex_init(&data->data_race, NULL) != 0)
   {
      ft_putstr_fd("Error: mutex init failed\n", 2);
      return;
   }
   if (pthread_mutex_init(&data->meals_lock, NULL) != 0)
   {
      ft_putstr_fd("Error: mutex init failed\n", 2);
      return;
   }
   if (pthread_mutex_init(&data->full_lock, NULL) != 0)
   {
      ft_putstr_fd("Error: mutex init failed\n", 2);
      return;
   }
}

int ft_init_data(t_data *data)
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
      return (1);
   }
   data->start_time = 0;
   ft_init_mutexes(data);
   return (0);
}

void *ft_philo(void *philo1)
{
   t_philo *philo;

   philo = (t_philo *)(philo1);
   if (philo->id % 2 == 0)
      ft_usleep(philo->data->time_to_eat, philo);
   while (ft_check_flags(philo))
   {
      if (philo->data->nb_philos == 1)
      {
         pthread_mutex_lock(philo->right_fork);
         ft_print(philo, "has taken a fork");
         pthread_mutex_unlock(philo->right_fork);
         return (NULL);
      }
      pthread_mutex_lock(philo->right_fork);
      ft_print(philo, "has taken a fork");
      pthread_mutex_lock(philo->left_fork);
      ft_print(philo, "has taken a fork");
      ft_print(philo, "is eating");
      ft_usleep(philo->data->time_to_eat, philo);

      pthread_mutex_lock(&philo->data->data_race);
      philo->last_time_eating = get_time();
      pthread_mutex_unlock(&philo->data->data_race);

      pthread_mutex_lock(&philo->data->meals_lock);
      philo->meals++;
      pthread_mutex_unlock(&philo->data->meals_lock);

      pthread_mutex_unlock(philo->right_fork);
      pthread_mutex_unlock(philo->left_fork);

      ft_print(philo, "is sleeping");
      ft_usleep(philo->data->time_to_sleep, philo);

      ft_print(philo, "is thinking");
   }
   return (NULL);
}

int ft_check_last_time_eating(t_philo *philo, int i)
{
   pthread_mutex_lock(&philo->data->data_race);
   if ((get_time() - philo[i].last_time_eating) >= philo->data->time_to_die)
   {
      pthread_mutex_unlock(&philo->data->data_race);
      return 1;
   }
   pthread_mutex_unlock(&philo->data->data_race);
   return (0);
}

int ft_check_death(t_philo *philo)
{
   int i = 0;

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

int ft_check_full(t_philo *philo)
{
   int i = 0;
   int countmeals = 0;

   while (i < philo->data->nb_philos)
   {
      pthread_mutex_lock(&philo->data->meals_lock);
      if (philo->data->nb_must_eat != -1 && philo[i].meals >= philo->data->nb_must_eat)
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



void *ft_monitor(void *philo1)
{
   t_philo *philo = (t_philo *)philo1;
   while (1)
   {
      if (ft_check_death(philo) == 0)
         return (NULL);
      if (ft_check_full(philo) == 0)
         return (NULL);
      // ft_usleep(5);
   }
   return (NULL);
}

int ft_init_philos(t_data *data)
{
   int i;
   pthread_t monitor = NULL;

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
      if (pthread_create(&data->philos[i].thread, NULL, ft_philo, &data->philos[i]) != 0)
      {
         ft_putstr_fd("Error: thread creation failed\n", 2);
         return (1);
      }
      i++;
   }
   pthread_create(&monitor, NULL, ft_monitor, data->philos);
   if (pthread_join(monitor, NULL) != 0)
   {
      ft_putstr_fd("Error: thread join failed\n", 2);
      return (1);
   }
   ft_join_threads(data);
   return (0);
}
