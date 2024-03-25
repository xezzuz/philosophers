/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nazouz <nazouz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 09:51:08 by nazouz            #+#    #+#             */
/*   Updated: 2024/03/25 02:51:24 by nazouz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	break_condition(t_data *data, int index, size_t time)
{
	pthread_mutex_lock(&data->lock);
	if (time >= data->philos[index].death_date)
	{
		data->dead = 1;
		pthread_mutex_unlock(&data->lock);
		print_state(data, index + 1, DIED);
		return (1);
	}
	if (data->stuffed_philos == data->philos_nbr)
		return (pthread_mutex_unlock(&data->lock), 1);
	pthread_mutex_unlock(&data->lock);
	return (0);
}

int	a_philo_died(t_data *data)
{
	pthread_mutex_lock(&data->lock);
	if (data->dead)
	{
		pthread_mutex_unlock(&data->lock);
		return (1);
	}
	pthread_mutex_unlock(&data->lock);
	return (0);
}

void	*monitor(void *arg)
{
	int			i;
	t_data		*data;

	data = (t_data *)arg;
	i = 0;
	while (i < data->philos_nbr)
	{
		pthread_mutex_lock(&data->lock);
		if (data->philos[i].meals == data->max_meals)
		{
			pthread_mutex_unlock(&data->lock);
			i++;
			continue ;
		}
		pthread_mutex_unlock(&data->lock);
		if (break_condition(data, i, get_time()))
			break ;
		if (data->philos_nbr == i + 1)
			i = 0;
	}
	return (NULL);
}

void	*routine(void *arg)
{
	t_philo		*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		ft_usleep(philo->data->t_eat);
	while (1)
	{
		if (a_philo_died(philo->data))
			break ;
		eat(philo);
		pthread_mutex_lock(&philo->data->lock);
		if (philo->meals == philo->data->max_meals)
		{
			philo->data->stuffed_philos++;
			pthread_mutex_unlock(&philo->data->lock);
			break ;
		}
		pthread_mutex_unlock(&philo->data->lock);
		sleeeep(philo);
		print_state(philo->data, philo->id, THINKING);
	}
	return (NULL);
}

int	philosophers(t_data *data)
{
	int			i;

	data->start_time = get_time();
	i = 0;
	while (i < data->philos_nbr)
		data->philos[i++].death_date = data->start_time + data->t_die;
	if (pthread_create(&data->monitor, NULL, monitor, data))
		return (ENOTHD);
	i = -1;
	while (++i < data->philos_nbr)
		if (pthread_create(&data->philos[i].thread,
				NULL, routine, &data->philos[i]))
			return (ENOTHD);
	i = 0;
	while (i < data->philos_nbr)
		pthread_join(data->philos[i++].thread, NULL);
	pthread_join(data->monitor, NULL);
	return (0);
}
