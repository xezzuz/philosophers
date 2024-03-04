/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nazouz <nazouz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 09:00:17 by nazouz            #+#    #+#             */
/*   Updated: 2024/03/04 09:19:41 by nazouz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	t_philo_alloc(t_data *data)
{
	data->philos = malloc(sizeof(t_philo) * data->philos_nbr);
	if (!data->philos)
		return (0);
		// (printf("malloc error\n"), exit(0));
	data->forks = malloc(sizeof(t_fork) * data->philos_nbr);
	if (!data->forks)
		return (0);
		// (free(data->philos), printf("malloc error\n"), exit(0));
	return (1);
}

void	t_philo_init(t_data *data)
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
		pthread_mutex_init(&data->forks[i].fork, NULL);
		i++;
	}
}

int	t_data_init(t_data *data)
{
	if (!t_philo_alloc(data))
		; // malloc error
	t_philo_init(data);
	pthread_mutex_init(&data->lock, NULL);
	pthread_mutex_init(&data->write, NULL);
	return (1);
}
