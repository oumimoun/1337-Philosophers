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

# define PHILO_H

# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include <stdio.h>
# include <pthread.h>
# include <time.h>
# include <sys/time.h>

# define ERROR 1
# define SUCCESS 0

typedef struct s_philo
{
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*left_fork;
	pthread_t		check_death_thread;
	pthread_t		thread;
	struct s_data	*data;
	size_t			last_time_eating;
	int				meals;
	int				id;
}	t_philo;

typedef struct s_data
{
	pthread_mutex_t	print;
	pthread_mutex_t	full_lock;
	pthread_mutex_t	meals_lock;
	pthread_mutex_t	data_race;
	pthread_mutex_t	death_lock;
	pthread_mutex_t	*forks;
	t_philo			*philos;
	size_t			time_to_eat;
	size_t			time_to_die;
	size_t			time_to_sleep;
	size_t			start_time;
	int				nb_philos;
	int				die;
	int				full;
	int				nb_must_eat;
}	t_data;

int		ft_atoi(char *str);
int		ft_init_philos(t_data *data);
int		ft_print(t_philo *philo, char *str);
int		ft_check_flags(t_philo *philo);
int		ft_check_full(t_philo *philo);
int		ft_check_death(t_philo *philo);
int		ft_parse_args(int ac, char **av, t_data *data);
int		ft_check_last_time_eating(t_philo *philo, int i);
int		ft_init_data(t_data *data);
int		destroy_mutexes(t_data *data);

void	ft_join_threads(t_data *data);
void	ft_usleep(size_t milliseconds, t_philo *philo);
void	ft_putstr_fd(char *s, int fd);
void	*ft_philo(void *data);
void	*ft_monitor(void *philos);

size_t	get_time(void);

#endif
