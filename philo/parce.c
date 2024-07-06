/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parce.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oumimoun <oumimoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 09:11:42 by oumimoun          #+#    #+#             */
/*   Updated: 2024/07/06 14:14:04 by oumimoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
      return (1);
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
   data->die = 0;
   data->full = 0;
   if (ac == 6)
      data->nb_must_eat = ft_atoi(av[5]);
   if (data->nb_philos < 1 || data->time_to_die < 0 || data->time_to_eat < 0 || data->time_to_sleep < 0 || (ac == 6 && data->nb_must_eat < 1))
   {
      printf("Error: wrong arguments\n");
      return (1);
   }
   return (0);
}
