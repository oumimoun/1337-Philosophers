/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parce.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oumimoun <oumimoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 09:11:42 by oumimoun          #+#    #+#             */
/*   Updated: 2024/07/07 15:22:38 by oumimoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_parse_args(int ac, char **av, t_data *data)
{
	if (ac < 5 || ac > 6)
		return (ERROR);
	if (ft_atoi(av[1]) < 1 || ft_atoi(av[2]) == -1 \
		|| ft_atoi(av[3]) == -1 || ft_atoi(av[4]) == -1)
		return (ERROR);
	data->nb_philos = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	data->nb_must_eat = -1;
	data->die = 0;
	data->full = 0;
	if (ac == 6)
		data->nb_must_eat = ft_atoi(av[5]);
	if ((ac == 6 && data->nb_must_eat < 1))
		return (ERROR);
	return (SUCCESS);
}
