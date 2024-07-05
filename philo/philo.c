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

int ft_check(t_philo *philo)
{
   pthread_mutex_lock(&philo->data->data_race);
   if (philo->data->die == 1)
   {
      pthread_mutex_unlock(&philo->data->data_race);
      return (0);
   }
   pthread_mutex_unlock(&philo->data->data_race);
   return (1);
}

int ft_isdigit(int d)
{
   if (d >= '0' && d <= '9')
      return (1);
   return (0);
}

int ft_double_check(int ac, char **av)
{
   int i;
   int j;
   char *str;

   i = 0;
   while (i < ac)
   {
      j = 0;
      str = av[i];
      if (str[j] == '+')
         j++;
      while (str[j])
      {
         if (!(str[j] >= '0' && str[j] <= '9'))
            return (1);
         j++;
      }
      i++;
   }
   return 0;
}

int ft_check_args(int ac, char **av)
{
   int i;
   int j;

   if (ac < 5 || ac > 6)
   {
      ft_putstr_fd("Error: wrong number of arguments\n", 2);
      return (1);
   }
   i = 1;
   while (i < ac)
   {
      j = 0;
      while (av[i][j])
      {
         if (ft_isdigit(av[i][j]) || av[i][j] == '+')
            j++;
         else
            return (1);
      }
      i++;
   }
   return (0);
}

int ft_parse_args(int ac, char **av, t_data *data)
{
   data->nb_philos = ft_atoi(av[1]);
   data->time_to_die = ft_atoi(av[2]);
   data->time_to_eat = ft_atoi(av[3]);
   data->time_to_sleep = ft_atoi(av[4]);
   data->nb_must_eat = -1;
   if (ac == 6)
      data->nb_must_eat = ft_atoi(av[5]);
   // if (data->nb_philos < 1 || data->time_to_die < 0 || data->time_to_eat < 0 || data->time_to_sleep < 0 || (ac == 6 && data->nb_must_eat < 1))
   // {
   //    printf("Error: wrong arguments\n");
   //    return (1);
   // }
   data->die = 0;
   return (0);
}

int ft_init_data(t_data *data)
{
   data->philos = malloc(sizeof(t_philo) * data->nb_philos);
   if (data->philos == NULL)
   {
      ft_putstr_fd("Error: malloc failed\n", 2);
      return (1);
   }
   data->start_time = get_time();
   data->forks = malloc(sizeof(pthread_mutex_t) * data->nb_philos);
   if (data->forks == NULL)
   {
      ft_putstr_fd("Error: malloc failed\n", 2);
      return (1);
   }
   if (pthread_mutex_init(&data->print, NULL) != 0)
   {
      ft_putstr_fd("Error: mutex init failed\n", 2);
      return (1);
   }
   if (pthread_mutex_init(&data->death_lock, NULL) != 0)
   {
      ft_putstr_fd("Error: mutex init failed\n", 2);
      return (1);
   }
   if (pthread_mutex_init(&data->data_race, NULL) != 0)
   {
      ft_putstr_fd("Error: mutex init failed\n", 2);
      return (1);
   }
   return (0);
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

   if (ft_check(philo))
   {
      pthread_mutex_lock(&philo->data->print);
      time = get_time() - philo->data->start_time;
      printf("%zu %d %s\n", time, philo->id, str);
      pthread_mutex_unlock(&philo->data->print);
   }
   return (0);
}

int ft_usleep(size_t milliseconds)
{
   size_t start;

   start = get_time();
   while ((get_time() - start) < milliseconds)
      usleep(500);
   return (0);
}

void *ft_philo(void *data)
{
   t_philo *philo;
   // size_t time;

   philo = (t_philo *)(data);
   if (philo->id % 2 == 1)
      usleep(500);
   while (ft_check(philo))
   {
      pthread_mutex_lock(&philo->data->forks[philo->id]);
      ft_print(philo, "has taken a fork");
      pthread_mutex_lock(&philo->data->forks[(philo->id + 1) % philo->data->nb_philos]);
      ft_print(philo, "has taken a fork");

      ft_print(philo, "is eating");
      ft_usleep(philo->data->time_to_eat);

      // time = get_time();
      // pthread_mutex_lock(&philo->data->data_race);
      // // if (philo->data->nb_must_eat != -1 && philo->meals > philo->data->nb_must_eat)
      // // {
      // //    philo->data->die = 1;
      // //    pthread_mutex_unlock(&philo->data->death_lock);
      // //    return (NULL);
      // // }
      // if ( philo->data->die == 1)
      //    break ;
      // pthread_mutex_unlock(&philo->data->data_race);

      pthread_mutex_lock(&philo->data->data_race);
      philo->last_time_eating = get_time();
      philo->meals++;
      pthread_mutex_unlock(&philo->data->data_race);

      pthread_mutex_unlock(&philo->data->forks[philo->id]);
      pthread_mutex_unlock(&philo->data->forks[(philo->id + 1) % philo->data->nb_philos]);

      ft_print(philo, "is sleeping");
      ft_usleep(philo->data->time_to_sleep);

      ft_print(philo, "is thinking");
      // usleep(50);
   }
   return (NULL);
}

void *ft_monitor(void *philo1)
{
   int i = 0;
   t_philo *philo = (t_philo *)philo1;
   while (1 && philo)
   {
      pthread_mutex_lock(&philo->data->death_lock);
      if (get_time() - philo[i % philo->data->nb_philos].last_time_eating >= (size_t)philo[i % philo->data->nb_philos].data->time_to_die)
      {
         // if (philo[i % philo->data->nb_philos].data->die == 1)
         // {
         //    pthread_mutex_lock(&philo[i % philo->data->nb_philos].data->print);
         //    ft_print(&philo[i % philo->data->nb_philos], "died");
         //     return (NULL);
         // }
         ft_print(&philo[i % philo->data->nb_philos], "died");
         philo[i % philo->data->nb_philos].data->die = 1;
         pthread_mutex_unlock(&philo->data->death_lock);
         return (NULL);
      }
      i++;
      pthread_mutex_unlock(&philo->data->death_lock);
      usleep(10);
   }
   return (NULL);
}

int destroy_mutexes(t_data *data)
{
   int i;

   i = 0;
   while (i < data->nb_philos)
   {
      pthread_mutex_destroy(&data->forks[i]);
      i++;
   }
   pthread_mutex_destroy(&data->print);
   pthread_mutex_destroy(&data->death_lock);
   pthread_mutex_destroy(&data->data_race);
   return (0);
}

int ft_init_philos(t_data *data)
{
   int i;
   pthread_t monitor = NULL;

   i = 0;
   pthread_create(&monitor, NULL, ft_monitor, data->philos);
   while (i < data->nb_philos)
   {
      data->philos[i].id = i + 1;
      data->philos[i].data = data;
      data->philos[i].flag = 0;
      data->philos[i].alive = 1;
      data->philos[i].meals = 0;
      data->philos[i].last_time_eating = get_time();
      if (pthread_mutex_init(&data->forks[i], NULL) != 0)
      {
         printf("Error: mutex init failed\n");
         return (1);
      }
      if (pthread_create(&data->philos[i].thread, NULL, ft_philo, &data->philos[i]) != 0)
      {
         printf("Error: thread creation failed\n");
         return (1);
      }
      i++;
   }

   i = 0;
   while (i < data->nb_philos)
   {
      if (pthread_join(data->philos[i].thread, NULL) != 0)
      {
         printf("Error: thread join failed\n");
         return (1);
      }
      i++;
   }
   if (pthread_join(monitor, NULL) != 0)
   {
      printf("Error: thread join failed\n");
      return (1);
   }
   return (0);
}
