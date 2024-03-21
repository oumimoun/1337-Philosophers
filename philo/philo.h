/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oumimoun <oumimoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 19:33:24 by oumimoun          #+#    #+#             */
/*   Updated: 2024/03/20 23:10:14 by oumimoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H

#define PHILO_H

#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <stdio.h>
#include <pthread.h>
#include <time.h>
#include <sys/time.h>

#define MAX_PHILOSOPHERS 10

pthread_mutex_t forks[MAX_PHILOSOPHERS];

typedef struct s_data
{
    int nb_philo;
    int time_to_die;
    int time_to_eat;
    int time_to_sleep;
    int nb_must_eat;
    int times_eaten;
    pthread_mutex_t *forks;
    // long start_time;

} t_philo;

int	ft_atoi(char *str);


#endif
