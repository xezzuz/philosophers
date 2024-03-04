/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nazouz <nazouz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 09:00:17 by nazouz            #+#    #+#             */
/*   Updated: 2024/03/04 18:12:13 by nazouz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	destroy_mutexes(t_data *data, int stop)
{
	int			i;

	i = 0;
	while (i < stop)
		pthread_mutex_destroy(&data->forks[i++].fork);
	ft_putstr_fd("pthread_mutex_init() failed\n", STDERR_FILENO);
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
		data->philos[i].left_fork = &data->forks[i];
		data->philos[i].right_fork = &data->forks[(i + 1) % data->philos_nbr];
		data->philos[i].left_fork->fork_id = i;
		data->philos[i].right_fork->fork_id = (i + 1) % data->philos_nbr;
		if (pthread_mutex_init(&data->forks[i].fork, NULL))
			return (destroy_mutexes(data, i), ENOMTX);
		i++;
	}
	return (0);
}

int	t_data_init(t_data *data)
{
	data->philos = malloc(sizeof(t_philo) * data->philos_nbr);
	if (!data->philos)
		return (ft_putstr_fd("malloc() failed\n", STDERR_FILENO), ENOMEM);
	data->forks = malloc(sizeof(t_fork) * data->philos_nbr);
	if (!data->forks)
		return (ft_putstr_fd("malloc() failed\n", STDERR_FILENO),
			free(data->philos), ENOMEM);
	if (t_philo_init(data))
		return (free(data->philos), free(data->forks), ENOMTX);
	if (pthread_mutex_init(&data->lock, NULL))
		return (free(data->philos), free(data->forks),
			destroy_mutexes(data, data->philos_nbr), ENOMTX);
	if (pthread_mutex_init(&data->write, NULL))
		return (free(data->philos),
			free(data->forks), pthread_mutex_destroy(&data->lock),
				destroy_mutexes(data, data->philos_nbr), ENOMTX);
	return (0);
}
