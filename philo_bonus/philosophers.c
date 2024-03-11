/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nazouz <nazouz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 09:51:08 by nazouz            #+#    #+#             */
/*   Updated: 2024/03/11 15:59:47 by nazouz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

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
			exit(I_DIED);
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
			exit(IM_FULL);
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
	i = 0;
	while (i < data->philos_nbr)
	{
		data->philos[i].death_date = data->start_time + data->t_die;
		pid = fork();
		if (pid < 0)
			perror("fork");
		if (pid > 0) // parent
			data->philos[i].process_id = pid;
		else if (!pid) // philo [i]
			break ;
		i++;
	}
	if (!pid)
		routine(&data->philos[i]);
	// wait for children
	else
	{
		pid = 0;
		while (1)
		{
			pid = waitpid(-1, &exit_code, 0);
			printf("========> Child exited [%d] [%d]\n", pid, WEXITSTATUS(exit_code));
			if (WEXITSTATUS(exit_code) == I_DIED)
			{
				i = 0;
				while (i < data->philos_nbr)
				{
					if (kill(data->philos[i++].process_id, SIGTERM) == -1)
						perror("kill");
				}
				exit(0);
			}
			if (pid < 0)
			{
				perror("waitpid");
				break ;
			}
		}
		printf("DONE\n");
		sem_close(data->forks);
        sem_unlink("/forks");
	}
	return (0);
}
