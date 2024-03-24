/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nazouz <nazouz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 10:29:11 by nazouz            #+#    #+#             */
/*   Updated: 2024/03/21 20:12:29 by nazouz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

# define ENOMEM 12
# define ENOMTX 21
# define ENOTHD 42
# define EATING 1
# define SLEEPING 2
# define THINKING 3
# define DIED 4
# define PICK_UP 5
# define PUT_DOWN 6

typedef struct s_data	t_data;

typedef struct s_fork
{
	int				fork_id;
	pthread_mutex_t	fork;
}				t_fork;

typedef struct s_philo
{
	int			id;
	pthread_t	thread;
	long		meals;
	size_t		death_date;
	t_data		*data;
	t_fork		*left_fork;
	t_fork		*right_fork;
}				t_philo;

typedef struct s_data
{
	pthread_t			monitor;
	long				philos_nbr;
	long				t_eat;
	long				t_sleep;
	long				t_die;
	long				max_meals;
	long				start_time;
	int					dead;
	int					stuffed_philos;
	pthread_mutex_t		lock;
	pthread_mutex_t		write;
	t_philo				*philos;
	t_fork				*forks;
}						t_data;

int			parse(t_data *data, char **argv);
int			t_data_init(t_data *data);
int			philosophers(t_data *data);
void		eat(t_philo *philo);
void		sleeeep(t_philo *philo);
void		print_state(t_data *data, int philo_id, int state);
size_t		get_time(void);
int			ft_usleep(size_t milliseconds);
void		ft_putstr_fd(char *s, int fd);
long long	ft_atoll(const char *str);
int			a_philo_died(t_data *data);
void		ft_clean(t_data *data, int error);

#endif
