/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_bonus.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nazouz <nazouz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 10:29:11 by nazouz            #+#    #+#             */
/*   Updated: 2024/03/15 21:26:32 by nazouz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_BONUS_H
# define PHILOSOPHERS_BONUS_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <limits.h>
# include <pthread.h>
# include <semaphore.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <signal.h>

# define ENOMEM 12
# define EATING 1
# define SLEEPING 2
# define THINKING 3
# define DIED 4
# define PICK_UP 5
# define PUT_DOWN 6

typedef struct s_data	t_data;

typedef struct s_philo
{
	int			id;
	pid_t		process_id;
	pthread_t	thread;
	long		meals;
	size_t		death_date;
	char		*lock_str;
	sem_t		*lock;
	t_data		*data;
}				t_philo;

typedef struct s_data
{
	pid_t				monitor_id;
	long				philos_nbr;
	long				t_eat;
	long				t_sleep;
	long				t_die;
	long				max_meals;
	long				start_time;
	int					dead;
	int					stuffed_philos;
	sem_t				*forks;
	sem_t				*write;
	t_philo				*philos;
}						t_data;

int			parse(t_data *data, char **argv);
int			t_data_init(t_data *data);
int			philosophers(t_data *data);
void		eat(t_philo *philo);
void		sleeeep(t_philo *philo);
void		print_state(t_philo *philo, int philo_id, int state);
size_t		get_time(void);
int			ft_usleep(size_t milliseconds);
void		ft_putstr_fd(char *s, int fd);
long long	ft_atoll(const char *str);
char		*ft_strjoin(char const *s1, char const *s2);
char		*ft_strdup(const char *s1);
char		*ft_itoa(int n);
int			a_philo_died(t_data *data);
void		ft_clean(t_data *data);

#endif
