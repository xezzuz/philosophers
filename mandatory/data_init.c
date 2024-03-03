/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nazouz <nazouz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 19:51:17 by nazouz            #+#    #+#             */
/*   Updated: 2024/03/02 21:32:47 by nazouz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	t_data_init(t_data *data)
{
	int			i;

	data->philos = malloc(sizeof(t_philo) * data->philos_nbr);
	if (!data->philos)
		(printf("malloc error\n"), exit(0));
	data->forks = malloc(sizeof(t_fork) * data->philos_nbr);
	if (!data->forks)
		(free(data->philos), printf("malloc error\n"), exit(0));
	i = 0;
	while (i < data->philos_nbr)
	{
		data->philos[i].id = i + 1;
		data->philos[i].meals = 0;
		data->philos[i].last_meal = 0;
		data->philos[i].stuffed = 0;
		data->philos[i].left_fork = &data->forks[i];
		data->philos[i].left_fork->fork_id = i;
		data->philos[i].right_fork = &data->forks[(i + 1) % data->philos_nbr];
		data->philos[i].right_fork->fork_id = (i + 1) % data->philos_nbr;
		data->philos[i].data = data;
		pthread_mutex_init(&data->forks[i].fork, NULL);
		i++;
	}
	pthread_mutex_init(&data->meals_mutex, NULL);
	pthread_mutex_init(&data->start_mutex, NULL);
	pthread_mutex_init(&data->finish_mutex, NULL);
	pthread_mutex_lock(&data->start_mutex);
	data->start_time = get_time();
	pthread_mutex_unlock(&data->start_mutex);
	i = 0;
	while (i < data->philos_nbr)
	{
		if (pthread_create(&data->philos->thread, NULL, philo_routine, &data->philos[i]))
			(printf("thread creation failed!\n"), exit(0));
		i++;
	}
	if (pthread_create(&data->monitor, NULL, monitor_philos, data))
		(printf("thread creation failed!\n"), exit(0));
	i = 0;
	while (i < data->philos_nbr)
	{
		if (pthread_join(data->philos[i].thread, NULL))
			;
			// (printf("thread join failed!\n"), exit(0));
		i++;
	}
	if (pthread_join(data->monitor, NULL))
		;
			// (printf("thread join failed!\n"), exit(0));
	// all philos are full;
}
