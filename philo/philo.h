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
	struct s_data *data;
	pthread_t check_death_thread;
	pthread_t thread;
	int flag;
	int meals;
	int id;
	int alive;

} t_philo;

typedef struct s_data
{
	pthread_mutex_t print;
	pthread_mutex_t data_race;
	pthread_mutex_t *forks;
	pthread_mutex_t death_lock;
	size_t currnt_time;
	size_t *last_time_eating;
	int nb_philos;
	int time_to_eat;
	int time_to_die;
	int time_to_sleep;
	int die;
	int nb_must_eat;
	t_philo *philos;
	size_t start_time;
} t_data;

int ft_atoi(char *str);
void	ft_putstr_fd(char *s, int fd);
int ft_init_philos(t_data *data);
void *ft_philo(void *data);
int ft_print(t_philo *philo, char *str);

size_t get_time(void);

int ft_init_data(t_data *data);

int ft_parse_args(int ac, char **av, t_data *data);
int ft_check_args(int ac, char **av);
void	ft_putstr_fd(char *s, int fd);
int ft_double_check(int ac, char **av);






#endif
