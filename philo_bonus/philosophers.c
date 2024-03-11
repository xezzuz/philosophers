/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nazouz <nazouz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 09:51:08 by nazouz            #+#    #+#             */
/*   Updated: 2024/03/11 20:24:42 by nazouz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	wait_for_all(t_data *data)
{
	int		i;
	int		exit_code;

	while (1)
	{
		waitpid(-1, &exit_code, 0);
		if (WEXITSTATUS(exit_code))
		{
			i = 0;
			while (i < data->philos_nbr)
				kill(data->philos[i++].process_id, SIGTERM);
			return ;
		}
	}
}

int	spawn_children(t_data *data)
{
	int		i;
	int		pid;

	i = 0;
	while (i < data->philos_nbr)
	{
		data->philos[i].death_date = data->start_time + data->t_die;
		pid = fork();
		if (pid < 0)
			return (perror("fork"), -1);
		if (pid > 0)
			data->philos[i].process_id = pid;
		else if (!pid)
			break ;
		i++;
	}
	return (pid);
}

void	*monitor(void *arg)
{
	int			i;
	t_philo		*philo;
	size_t		time;

	philo = (t_philo *)arg;
	i = 0;
	while (1)
	{
		sem_wait(philo->lock);
		if (philo->meals == philo->data->max_meals)
		{
			i++;
			sem_post(philo->lock);
			continue ;
		}
		sem_post(philo->lock);
		time = get_time();
		sem_wait(philo->lock);
		if (time >= philo->death_date)
		{
			print_state(philo, philo->id, DIED);
			sem_post(philo->lock);
			exit(1);
		}
		sem_post(philo->lock);
	}
	return (NULL);
}

void	routine(t_philo *philo)
{
	pthread_create(&philo->thread, NULL, monitor, philo);
	if (philo->id % 2 == 0)
		ft_usleep(philo->data->t_eat);
	while (1)
	{
		eat(philo);
		if (philo->meals == philo->data->max_meals)
			exit(0);
		sleeeep(philo);
		print_state(philo, philo->id, THINKING);
	}
	exit(0);
}

int	philosophers(t_data *data)
{
	int			i;
	int			pid;
	int			exit_code;

	data->start_time = get_time();
	pid = spawn_children(data);
	if (pid == -1)
		return (1);
	if (!pid)
		routine(&data->philos[i]);
	// wait for children
	else
		wait_for_all(data);
	return (0);
}
