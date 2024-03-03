/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nazouz <nazouz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 10:29:11 by nazouz            #+#    #+#             */
/*   Updated: 2024/03/03 11:59:22 by nazouz           ###   ########.fr       */
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

# define EATING 1
# define SLEEPING 2
# define THINKING 3
# define DIED 4
# define PICK_UP 5
# define PUT_DOWN 6

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
	pthread_t	death_angel;
	long		meals;
	int			stuffed;
	long		last_meal;
	long		death_date;
	int			status;
	t_data		*data;
	t_fork		*left_fork;
	t_fork		*right_fork;
	pthread_mutex_t		lock;
}				t_philo;

typedef struct s_data
{
	pthread_t			waiter;
	long				philos_nbr;
	long				t_eat;
	long				t_sleep;
	long				t_die;
	long				stuffed_philos;
	long				max_meals;
	long				start_time;
	int					finish_sim;
	pthread_mutex_t		lock;
	pthread_mutex_t		write;
	t_philo				*philos;
	t_fork				*forks;
	// pthread_mutex_t	finish_mutex;
	// pthread_mutex_t	start_mutex;
	// pthread_mutex_t	meals_mutex;
}						t_data;

int			parse(t_data *data, char **argv);
int			t_data_init(t_data *data);
void		philosophers(t_data *data);
void		*philo_routine(void *arg);
void		*monitor_philos(void *arg);
void		eat(t_philo *philo);
void		sleeeep(t_philo *philo);
void		print_state(t_philo *philo, int state);
size_t		get_time(void);
int			ft_usleep(size_t milliseconds);
void		ft_putstr_fd(char *s, int fd);
long long	ft_atoll(const char *str);

#endif
