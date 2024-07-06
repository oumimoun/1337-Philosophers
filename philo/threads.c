/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oumimoun <oumimoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 09:07:04 by oumimoun          #+#    #+#             */
/*   Updated: 2024/07/06 09:15:49 by oumimoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void ft_join_threads(t_data *data)
{
    int i;

    i = 0;
    while (i < data->nb_philos)
    {
        if (pthread_join(data->philos[i].thread, NULL) != 0)
        {
            printf("Error: thread join failed\n");
            return;
        }
        i++;
    }
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
    pthread_mutex_destroy(&data->meals_lock);
    pthread_mutex_destroy(&data->full_lock);
    return (0);
}
