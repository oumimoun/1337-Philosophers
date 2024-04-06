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


typedef struct s_philo
{
	struct s_data		*data;
	pthread_t			check_death_thread;
	pthread_t			thread;
	int					flag;
	int					id;
    int                 alive;
    

}	t_philo;

typedef struct s_data
{
	pthread_mutex_t		print;
	pthread_mutex_t		data_race;
	pthread_mutex_t		*forks;
	size_t				currnt_time;
	size_t				*last_time_eating;
	int					nb_philos;
	int					time_to_eat;
	int					time_to_die;
	int					time_to_sleep;
	int					die;
	int					nb_must_eat;
	t_philo				*philos;
	size_t start_time;
}	t_data;

int	ft_atoi(char *str);


#endif
