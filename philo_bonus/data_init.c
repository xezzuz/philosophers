/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nazouz <nazouz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 09:00:17 by nazouz            #+#    #+#             */
/*   Updated: 2024/03/11 20:04:39 by nazouz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	create_semaphore(t_philo *philo)
{
	philo->lock_str = ft_strjoin("/lock_", ft_itoa(philo->id));
	sem_unlink(philo->lock_str);
	philo->lock = sem_open(philo->lock_str, O_CREAT, 0644, 1);
	if (philo->lock == SEM_FAILED)
		return (0);
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
		if (!create_semaphore(&data->philos[i]))
		{
			while (i >= 0)
			{
				sem_close(data->philos[i].lock);
				sem_unlink(data->philos[i].lock_str);
				free(data->philos[i--].lock_str);
			}
			return (0);
		}
		i++;
	}
	return (1);
}

int	t_data_init(t_data *data)
{
	data->philos = malloc(sizeof(t_philo) * data->philos_nbr);
	if (!data->philos)
		return (ft_putstr_fd("Philosophers: malloc() failed\n", STDERR_FILENO), ENOMEM);
	if (!t_philo_init(data))
		return (free(data->philos),
			ft_putstr_fd("Philosophers: sem_open() failed\n", STDERR_FILENO), 1);
	sem_unlink("/forks");
	data->forks = sem_open("/forks", O_CREAT, 0644, data->philos_nbr);
	if (data->forks == SEM_FAILED)
		return (free(data->philos),
			ft_putstr_fd("Philosophers: sem_open() failed\n", STDERR_FILENO), 1);
	sem_unlink("/write");
	data->write = sem_open("/write", O_CREAT, 0644, 1);
	if (data->write == SEM_FAILED)
	{
		sem_close(data->forks);
		sem_unlink("/forks");
		return (free(data->philos),
			ft_putstr_fd("Philosophers: sem_open() failed\n", STDERR_FILENO), 1);
	}
	return (0);
}
