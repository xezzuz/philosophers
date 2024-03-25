/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_bonus.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nazouz <nazouz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 10:29:11 by nazouz            #+#    #+#             */
/*   Updated: 2024/03/25 05:09:14 by nazouz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_BONUS_H
# define PHILOSOPHERS_BONUS_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <semaphore.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <signal.h>

# define ENOMEM 12
# define EATING "is eating"
# define SLEEPING "is sleeping"
# define THINKING "is thinking"
# define DIED "died"
# define PICK_UP "has taken a fork"

typedef struct s_data	t_data;

typedef struct s_philo
{
	int			id;
	pid_t		process_id;
	pthread_t	thread;
	long		meals;
	size_t		death_date;
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
	sem_t				*lock;
	sem_t				*forks;
	sem_t				*write;
	t_philo				*philos;
}						t_data;

int			parse(t_data *data, char **argv);
int			t_data_init(t_data *data);
int			philosophers(t_data *data);
void		eat(t_philo *philo);
void		sleeeep(t_philo *philo);
void		print_state(sem_t *write, int philo_id,
				char *state, size_t elapsed);
size_t		get_time(void);
int			ft_usleep(size_t milliseconds);
void		ft_putstr_fd(char *s, int fd);
int			ft_atoi(const char *str);
int			ft_strcmp(const char *s1, const char *s2);
char		*ft_strdup(const char *s1);
int			a_philo_died(t_data *data);
void		ft_clean(t_data *data);

#endif
