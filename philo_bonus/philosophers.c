/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nazouz <nazouz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 09:51:08 by nazouz            #+#    #+#             */
/*   Updated: 2024/03/15 02:49:11 by nazouz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

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
		if (philo->meals == philo->data->max_meals)
			exit(0);
		sem_wait(philo->lock);
		if (get_time() >= philo->death_date)
		{
			print_state(philo, philo->id, DIED);
			sem_post(philo->lock);
			exit(1);
		}
		sem_post(philo->lock);
	}
	exit(0);
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
			break ;
		sleeeep(philo);
		print_state(philo, philo->id, THINKING);
	}
	exit(0);
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
			return (ft_putstr_fd("Philo: fork() failed\n", 2), -1);
		if (pid > 0)
			data->philos[i].process_id = pid;
		else if (!pid)
			routine(&data->philos[i]);
		i++;
	}
	return (pid);
}

int	philosophers(t_data *data)
{
	int			pid;

	data->start_time = get_time();
	pid = spawn_children(data);
	if (pid == -1)
		return (1);
	if (pid > 0)
		wait_for_all(data);
	return (0);
}
