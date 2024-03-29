/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nazouz <nazouz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 09:51:08 by nazouz            #+#    #+#             */
/*   Updated: 2024/03/29 00:35:28 by nazouz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

void	wait_for_all(t_data *data)
{
	int		i;
	int		return_value;
	int		exit_code;

	i = 0;
	return_value = 1;
	while (return_value > 0)
	{
		return_value = waitpid(-1, &exit_code, 0);
		if (WEXITSTATUS(exit_code))
			while (i < data->philos_nbr)
				kill(data->philos[i++].process_id, SIGTERM);
	}
	return ;
}

void	*monitor(void *arg)
{
	t_philo		*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		sem_wait(philo->data->lock);
		if (philo->meals == philo->data->max_meals)
			return (sem_post(philo->data->lock), NULL);
		if (get_time() >= philo->death_date)
		{
			print_state(philo->data->write, philo->id,
				DIED, get_time() - philo->data->start_time);
			sem_post(philo->data->lock);
			exit(1);
		}
		sem_post(philo->data->lock);
	}
	return (NULL);
}

void	routine(t_philo *philo)
{
	if (pthread_create(&philo->thread, NULL, monitor, philo))
	{
		ft_putstr_fd("Philo: pthread_create() failed\n", 2);
		exit(1);
	}
	while (1)
	{
		eat(philo);
		sleeeep(philo);
		print_state(philo->data->write, philo->id,
			THINKING, get_time() - philo->data->start_time);
		if (philo->meals == philo->data->max_meals)
			break ;
	}
	pthread_join(philo->thread, NULL);
	exit(0);
}

int	spawn_children(t_data *data)
{
	int		i;
	int		pid;

	i = -1;
	while (++i < data->philos_nbr)
	{
		pid = fork();
		if (pid < 0)
			return (ft_putstr_fd("Philo: fork() failed\n", 2), -1);
		if (!pid)
		{
			if ((i + 1) % 2 == 0)
				ft_usleep(data->t_eat);
			routine(&data->philos[i]);
		}
		else
			data->philos[i].process_id = pid;
	}
	return (pid);
}

int	philosophers(t_data *data)
{
	int			pid;
	int			i;

	i = 0;
	pid = spawn_children(data);
	if (pid == -1)
	{
		while (i < data->philos_nbr)
			kill(data->philos[i++].process_id, SIGTERM);
		return (0);
	}
	if (pid > 0)
		wait_for_all(data);
	return (1);
}
