/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oumimoun <oumimoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 08:50:39 by oumimoun          #+#    #+#             */
/*   Updated: 2024/07/09 10:06:18 by oumimoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_free(t_data *data)
{
	free(data->philos);
	data->philos = NULL;
	free(data->forks);
	data->forks = NULL;
	free(data);
	data = NULL;
}

int	main(int ac, char **av)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (ERROR);
	if (ft_parse_args(ac, av, data) == ERROR)
	{
		ft_putstr_fd("Error: wrong arguments\n", 2);
		return ((free(data)), (data = NULL), (ERROR));
	}
	if (ft_init_data(data) == 1)
		return ((free(data)), (data = NULL), (ERROR));
	if (ft_init_philos(data) == ERROR)
		return ((ft_free(data)), (ERROR));
	if (destroy_mutexes(data) == ERROR)
		return ((ft_free(data)), (ERROR));
	ft_free(data);
	return (SUCCESS);
}
