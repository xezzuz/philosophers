/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nazouz <nazouz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 17:06:32 by nazouz            #+#    #+#             */
/*   Updated: 2024/03/02 21:45:11 by nazouz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	death_checker(t_philo *philo)
{
	long		since;

	pthread_mutex_lock(&philo->data->meals_mutex);
	// pthread_mutex_lock(&philo->data->start_mutex);
	if (!philo->meals)
		philo->last_meal = philo->data->start_time;
	// pthread_mutex_unlock(&philo->data->start_mutex);
	since = get_time() - philo->last_meal;
	if (since < 0)
		printf("elapsed time is negatif!!!!!\n");
	if (since >= philo->data->time_to_die)
	{
		// printf("elapsed time = %ld\n", since);
		pthread_mutex_unlock(&philo->data->meals_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->meals_mutex);
	return (0);
}

void	*monitor_philos(void *arg)
{
	t_data		*data;
	int			i;

	data = (t_data *)arg;
	// pthread_mutex_lock(&data->start_mutex);
	// while (!data->start_time)
	// {
	// 	pthread_mutex_unlock(&data->start_mutex);
	// 	pthread_mutex_lock(&data->start_mutex);
	// }
	// pthread_mutex_unlock(&data->start_mutex);

	pthread_mutex_lock(&data->finish_mutex);
	while (!data->finish)
	{
		i = 0;
		while (!data->finish && i < data->philos_nbr)
		{
			if (death_checker(&data->philos[i]))
				(printf("%ld %d died\n", get_time() - data->start_time, data->philos[i].id), data->finish = 1, exit(0));
			i++;
		}
		// ft_usleep(10);
	}
	pthread_mutex_unlock(&data->finish_mutex);
	// printf("finish = %d\n", data->finish);
	return (NULL);
}
