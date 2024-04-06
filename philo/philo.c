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

int ft_check_args(int ac, char **av)
{
   int i;
   int j;

   if (ac < 5 || ac > 6)
   {
      printf("Error: wrong number of arguments\n");
      return (1);
   }
   i = 1;
   while (i < ac)
   {
      j = 0;
      while (av[i][j])
      {
         if (av[i][j] < '0' || av[i][j] > '9')
         {
            printf("Error: wrong arguments\n");
            return (1);
         }
         j++;
      }
      i++;
   }
   return (0);
}

int ft_parce_args(int ac, char **av, t_data *data)
{
   data->nb_philos = ft_atoi(av[1]);
   printf("data->nb_philos = %d\n", data->nb_philos);
   data->time_to_die = ft_atoi(av[2]);
   printf("data->time_to_die = %d\n", data->time_to_die);
   data->time_to_eat = ft_atoi(av[3]);
   printf("data->time_to_eat = %d\n", data->time_to_eat);
   data->time_to_sleep = ft_atoi(av[4]);
   printf("data->time_to_sleep = %d\n", data->time_to_sleep);
   data->nb_must_eat = -1;
   if (ac == 6)
      data->nb_must_eat = ft_atoi(av[5]);
   printf("data->nb_must_eat = %d\n", data->nb_must_eat);
   if (data->nb_philos < 2 || data->time_to_die < 0 || data->time_to_eat < 0
      || data->time_to_sleep < 0 || (ac == 6 && data->nb_must_eat < 1))
   {
      printf("Error: wrong arguments\n");
      return (1);
   }
   return (0);
}


int ft_init_data(t_data *data)
{
   data->philos = malloc(sizeof(t_philo) * data->nb_philos);
   if (data->philos == NULL)
   {
      printf("Error: malloc failed\n");
      return (1);
   }
   data->last_time_eating = malloc(sizeof(size_t) * data->nb_philos);
   if (data->last_time_eating == NULL)
   {
      printf("Error: malloc failed\n");
      return (1);
   }
   data->forks = malloc(sizeof(pthread_mutex_t) * data->nb_philos);
   if (data->forks == NULL)
   {
      printf("Error: malloc failed\n");
      return (1);
   }
   return (0);
}

size_t get_time(void)
{
   struct timeval time;
   gettimeofday(&time, NULL);
   return ((size_t)(time.tv_sec * 1000 + time.tv_usec / 1000));
}

int ft_print(t_philo *philo, char *str)
{
   size_t time;

   pthread_mutex_lock(&philo->data->print);
   time = philo->data->currnt_time - philo->data->start_time;
   printf("%zu %d %s\n", time, philo->id, str);
   pthread_mutex_unlock(&philo->data->print);
   return (0);
}

void *ft_philo(void *data)
{
   size_t time;
   t_philo *philo;

   philo = (t_philo *)(data);
   time = philo->data->currnt_time - philo->data->start_time;
   if (time - philo->data->last_time_eating[philo->id - 1] > (size_t)philo->data->time_to_die)
   {
      ft_print(philo, "died");
      philo->alive = 0;
      return (NULL);
   }
   ft_print(philo, "is eating");
   ft_print(philo, "is sleeping");
   ft_print(philo, "is thinking");
   return (NULL);
}



int ft_init_philos(t_data *data)
{
   int i;

   i = 0;
   while (i < data->nb_philos)
   {
      data->philos[i].id = i + 1;
      data->philos[i].data = data;
      data->philos[i].flag = 0;
      data->philos[i].alive = 1;
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
   return (0);
}

int main(int ac, char **av)
{
   t_data	*data;

   data = NULL;
   if(ft_check_args(ac, av) == 1)
      return (1);
   data = malloc(sizeof(t_data));
   if(ft_parce_args(ac, av, data) == 1)
      return (1);
   if (ft_init_data(data) == 1)
      return (1);
   if(ft_init_philos(data) == 1)
      return (1);
   

   return 0;
}

