/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nazouz <nazouz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 09:51:08 by nazouz            #+#    #+#             */
/*   Updated: 2024/03/04 16:37:58 by nazouz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

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

/*
*	monitor of all philosophers
*	checks death date and reports it
*/

void	*monitor(void *arg)
{
	int			i;
	t_data		*data;
	size_t		time;

	data = (t_data *)arg;
	i = 0;
	// loop on all philos and check their death date
	while (i < data->philos_nbr)
	{
		time = get_time();
		pthread_mutex_lock(&data->lock);
		if (time >= data->philos[i].death_date) // ACCESS DEATH DATE
		{
			data->dead = 1;						// ASSIGNING DEAD FLAG
			pthread_mutex_unlock(&data->lock);
			print_state(data, i + 1, DIED);
			break ;
		}
		if (data->stuffed_philos == data->philos_nbr)
		{
			pthread_mutex_unlock(&data->lock);
			break ;
		}
		pthread_mutex_unlock(&data->lock);
		i++;
		if (i == data->philos_nbr)
			i = 0;
	}
	return (NULL);
}

/*
*	single philosopher
*	eat, sleep, think
*	until he's stuffed or someone died
*/

void	*routine(void *arg)
{
	t_philo		*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		ft_usleep(philo->data->t_eat);
	// loop until philo is stuffed
	while (1)
	{
		if (a_philo_died(philo->data))
			break ;
		eat(philo);
		if (philo->meals == philo->data->max_meals)
		{
			pthread_mutex_lock(&philo->data->lock);
			philo->data->stuffed_philos++;
			pthread_mutex_unlock(&philo->data->lock);
			break ;
		}
		sleeeep(philo);
		print_state(philo->data, philo->id, THINKING);
	}
	return (NULL);
}

void	philosophers(t_data *data)
{
	int			i;

	// set start time
	data->start_time = get_time();
	// set death dates
	i = 0;
	while (i < data->philos_nbr)
		data->philos[i++].death_date = data->start_time + data->t_die;
	// launch monitor thread
	pthread_create(&data->monitor, NULL, monitor, data);
	// launch philosophers threads
	i = 0;
	while (i < data->philos_nbr)
	{
		pthread_create(&data->philos[i].thread, NULL, routine, &data->philos[i]);
		i++;
	}
	// join all philosophers
	i = 0;
	while (i < data->philos_nbr)
	{
		pthread_join(data->philos[i].thread, NULL);
		i++;
	}
	// join monitor
	pthread_join(data->monitor, NULL);
}
