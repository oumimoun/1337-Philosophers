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
	pthread_mutex_t *right_fork;
	pthread_mutex_t *left_fork;
	pthread_t thread;
	size_t last_time_eating;
	int flag;
	int meals;
	int id;
	int alive;

} t_philo;

typedef struct s_data
{
	pthread_mutex_t print;
	pthread_mutex_t full_lock;
	pthread_mutex_t meals_lock;
	pthread_mutex_t data_race;
	pthread_mutex_t death_lock;
	pthread_mutex_t *forks;
	size_t currnt_time;
	int nb_philos;
	int time_to_eat;
	size_t time_to_die;
	int time_to_sleep;
	int die;
	int full;
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

int destroy_mutexes(t_data *data);

void ft_join_threads(t_data *data);
int destroy_mutexes(t_data *data);

void ft_usleep(size_t milliseconds);

int ft_print(t_philo *philo, char *str);
void ft_putstr_fd(char *s, int fd);

size_t get_time(void);
int ft_parse_args(int ac, char **av, t_data *data);

int ft_double_check(int ac, char **av);
int ft_isdigit(int d);

int ft_check_flags(t_philo *philo);





#endif
