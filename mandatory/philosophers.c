/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nazouz <nazouz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 09:51:08 by nazouz            #+#    #+#             */
/*   Updated: 2024/03/03 18:05:18 by nazouz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	a_philo_died(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->lock);
	if (philo->data->finish_sim)
	{
		pthread_mutex_unlock(&philo->data->lock);
		printf("%ld | PHILO IS DEAD | REPORTED BY PHILO[%d]\n", get_time() - philo->data->start_time, philo->id);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->lock);
	pthread_mutex_lock(&philo->lock);
	if (philo->stuffed)
	{
		pthread_mutex_unlock(&philo->lock);
		return (1);
	}
	pthread_mutex_unlock(&philo->lock);
	return (0);
}

/*
*	he watches all the philos
*	checks if all philos are stuffed
*	if true he report finish_simulation
*/

void	*waiter(void *arg)
{
	t_data		*data;

	data = (t_data *)arg;
	while (1)
	{
		pthread_mutex_lock(&data->lock);
		if (data->stuffed_philos >= data->philos_nbr)
		{
			data->finish_sim = 1;
			pthread_mutex_unlock(&data->lock);
			return (NULL);
		}
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
	while (1)
	{
		current_time = get_time();
		pthread_mutex_lock(&philo->lock);
		if (current_time >= philo->death_date)
		{
			print_state(philo, DIED);
			pthread_mutex_lock(&philo->data->lock);
			philo->data->finish_sim = 1;
			pthread_mutex_unlock(&philo->data->lock);
			pthread_mutex_unlock(&philo->lock);
			return (NULL);
		}
		pthread_mutex_unlock(&philo->lock);
		pthread_mutex_lock(&philo->lock);
		if (philo->meals == philo->data->max_meals)
		{
			philo->stuffed = 1;
			philo->data->stuffed_philos++;
			pthread_mutex_unlock(&philo->lock);
			return (NULL);
		}
		pthread_mutex_unlock(&philo->lock);
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
	pthread_mutex_lock(&philo->data->lock);
	while (!philo->data->start_time)
		;
	pthread_mutex_unlock(&philo->data->lock);
	// philo->death_date = get_time() + philo->data->t_die;
	philo->death_date = philo->data->start_time + philo->data->t_die;
	// launch a supervisor
	pthread_create(&philo->death_angel, NULL, death_angel, philo);
	if (philo->id % 2 == 0)
		ft_usleep(philo->data->t_eat);
	// loop until someone die or all philos are stuffed
	while (1)
	{
		if (a_philo_died(philo))
			break ;
		eat(philo);
		if (a_philo_died(philo))
			break ;
		sleeeep(philo);
		if (a_philo_died(philo))
			break ;
		print_state(philo, THINKING);
	}
	// join supervisor
	pthread_join(philo->death_angel, NULL);
	return (NULL);
}

void	philosophers(t_data *data)
{
	int			i;
	// launch monitor if max_meals > 0
	if (data->max_meals > 0)
	{
		pthread_create(&data->waiter, NULL, waiter, data);
	}
	// launch philosophers threads
	i = 0;
	pthread_mutex_lock(&data->lock);
	while (i < data->philos_nbr)
	{
		pthread_create(&data->philos[i].thread, NULL, routine, &data->philos[i]);
		i++;
	}
	// set start time
	data->start_time = get_time();
	pthread_mutex_unlock(&data->lock);
	// join all threads
	i = 0;
	while (i < data->philos_nbr)
	{
		pthread_join(data->philos[i].thread, NULL);
		i++;
	}
	pthread_join(data->waiter, NULL);
}
