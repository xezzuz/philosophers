/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nazouz <nazouz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 09:51:08 by nazouz            #+#    #+#             */
/*   Updated: 2024/03/03 11:58:47 by nazouz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/*
*	he watches all the philos
*	checks if all philos are stuffed
*	if true he report finish_simulation
*/

void	*waiter(void *arg)
{
	t_data		*data;

	data = (t_data *)arg;
	while (!data->finish_sim)
	{
		pthread_mutex_lock(&data->lock);
		if (data->stuffed_philos >= data->philos_nbr)
			data->finish_sim = 1;
		pthread_mutex_unlock(&data->lock);
	}
	return (NULL);
}

/*
*	death angel of each philosopher
*	checks death date and reports it
*	checks if philo is stuffed
*/

void	*death_angel(void *arg)
{
	t_philo		*philo;
	long		current_time;

	philo = (t_philo *)arg;
	pthread_mutex_lock(&philo->data->lock);
	while (!philo->data->finish_sim)
	{
		current_time = get_time();
		if (current_time >= philo->death_date)
		{
			print_state(philo, DIED);
			pthread_mutex_lock(&philo->data->lock);
			philo->data->finish_sim = 1;
			pthread_mutex_unlock(&philo->data->lock);
		}
		pthread_mutex_lock(&philo->data->lock);
		if (philo->meals == philo->data->max_meals)
		{
			philo->stuffed = 1;
			philo->data->stuffed_philos++;
		}
		pthread_mutex_unlock(&philo->data->lock);
	}
	pthread_mutex_lock(&philo->data->lock);
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
	// launch a supervisor
	pthread_create(&philo->death_angel, NULL, death_angel, philo);
	// set death_date
	philo->death_date = get_time() + philo->data->t_die;
	// loop until someone die or all philos are stuffed
	while (!philo->data->finish_sim)
	{
		eat(philo);
		sleeeep(philo);
		print_state(philo, THINKING);
	}
	// join supervisor
	pthread_join(philo->death_angel, NULL);
	return (NULL);
}

void	philosophers(t_data *data)
{
	int			i;
	// set start time
	data->start_time = get_time();
	// launch monitor if max_meals > 0
	if (data->max_meals > 0)
	{
		pthread_create(&data->waiter, NULL, waiter, data);
	}
	// launch philosophers threads
	i = 0;
	while (i < data->philos_nbr)
	{
		pthread_create(&data->philos[i].thread, NULL, routine, &data->philos[i]);
		i++;
	}
	// join all threads
	i = 0;
	while (i < data->philos_nbr)
	{
		pthread_join(data->philos[i].thread, NULL);
		i++;
	}
	pthread_join(data->waiter, NULL);
}
