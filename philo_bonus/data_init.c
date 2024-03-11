/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nazouz <nazouz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 09:00:17 by nazouz            #+#    #+#             */
/*   Updated: 2024/03/11 15:59:06 by nazouz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	create_semaphore(t_philo *philo)
{
	philo->lock_str = ft_strjoin("/lock_", ft_itoa(philo->id));
	sem_unlink(philo->lock_str);
	philo->lock = sem_open(philo->lock_str, O_CREAT, 0644, 1);
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
		create_semaphore(&data->philos[i]);
		i++;
	}
	return (0);
}

int	t_data_init(t_data *data)
{
	data->philos = malloc(sizeof(t_philo) * data->philos_nbr);
	if (!data->philos)
		return (ft_putstr_fd("malloc() failed\n", STDERR_FILENO), ENOMEM);
	t_philo_init(data);
	// forks
	sem_unlink("/forks");
	data->forks = sem_open("/forks", O_CREAT, 0644, data->philos_nbr);
	// write sem
	sem_unlink("/write");
	data->write = sem_open("/write", O_CREAT, 0644, 1);
	return (0);
}
