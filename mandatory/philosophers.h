/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nazouz <nazouz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 10:29:11 by nazouz            #+#    #+#             */
/*   Updated: 2024/03/02 19:50:34 by nazouz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
#define PHILOSOPHERS_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <limits.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_data t_data;

typedef struct s_fork
{
	int				fork_id;
	pthread_mutex_t	fork;
}				t_fork;

typedef struct s_philo
{
	int			id;
	pthread_t	thread;
	t_fork		*left_fork;
	t_fork		*right_fork;
	long		meals;
	int			stuffed;
	long		last_meal;
	t_data		*data;
}				t_philo;

typedef struct s_data
{
	
	long		philos_nbr;
	long		time_to_eat;
	long		time_to_sleep;
	long		time_to_die;
	long		max_meals;
	long		start_time;
	int			finish;
	pthread_mutex_t	meals_mutex;
	pthread_mutex_t	start_mutex;
	pthread_mutex_t	finish_mutex;
	pthread_t	monitor;
	t_philo		*philos;
	t_fork		*forks;
}				t_data;

int			parse(t_data *data, char **argv);
void		t_data_init(t_data *data);
void		*philo_routine(void *arg);
void		*monitor_philos(void *arg);
size_t		get_time(void);
int			ft_usleep(size_t milliseconds);
void		ft_putstr_fd(char *s, int fd);
long long	ft_atoll(const char *str);

#endif
