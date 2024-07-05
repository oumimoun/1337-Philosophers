/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oumimoun <oumimoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 08:50:39 by oumimoun          #+#    #+#             */
/*   Updated: 2024/07/04 19:55:18 by oumimoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int main(int ac, char **av)
{
   t_data	*data;

   data = NULL;
   if(ft_check_args(ac, av) == 1)
   {
      ft_putstr_fd("Error: wrong arguments\n", 2);
      return (1);
   }
   // if (ft_double_check(ac, av) == 1)
   // {
   //    ft_putstr_fd("Error: wrong arguments\n", 2);
   //    return (1);
   // }
   
   data = malloc(sizeof(t_data));
   if(ft_parse_args(ac, av, data) == 1)
      return (1);
   if (ft_init_data(data) == 1)
      return (1);
   if(ft_init_philos(data) == 1)
      return (1);
   if (destroy_mutexes(data) == 1)
      return (1);
   
   

   return 0;
}
