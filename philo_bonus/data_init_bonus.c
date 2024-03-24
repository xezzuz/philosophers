/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_init_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nazouz <nazouz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 09:00:17 by nazouz            #+#    #+#             */
/*   Updated: 2024/03/19 22:45:25 by nazouz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

int	open_semaphores(t_data *data)
{
	sem_unlink("forks");
	sem_unlink("write");
	sem_unlink("lock");
	data->forks = sem_open("forks", O_CREAT, 0644, data->philos_nbr);
	data->write = sem_open("write", O_CREAT, 0644, 1);
	data->lock = sem_open("lock", O_CREAT, 0644, 1);
	if (data->forks == SEM_FAILED
		|| data->write == SEM_FAILED
		|| data->lock == SEM_FAILED)
	{
		(sem_close(data->forks), sem_close(data->write), sem_close(data->lock));
		return (free(data->philos),
			ft_putstr_fd("Philo: sem_open() failed\n", STDERR_FILENO), 0);
	}
	return (1);
}

int	t_philo_init(t_data *data)
{
	int			i;

	i = 0;
	while (i < data->philos_nbr)
	{
		data->philos[i].id = i + 1;
		data->philos[i].meals = 0;
		data->philos[i].data = data;
		data->philos[i].death_date = data->start_time + data->t_die;
		i++;
	}
	return (1);
}

int	t_data_init(t_data *data)
{
	data->philos = malloc(sizeof(t_philo) * data->philos_nbr);
	if (!data->philos)
		return (ft_putstr_fd("Philo: malloc() failed\n", STDERR_FILENO), 0);
	if (!open_semaphores(data))
		return (0);
	data->start_time = get_time();
	t_philo_init(data);
	return (1);
}
