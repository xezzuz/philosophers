/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nazouz <nazouz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 10:36:13 by nazouz            #+#    #+#             */
/*   Updated: 2024/03/02 21:48:19 by nazouz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	think(t_philo *philo)
{
	printf("%ld %d is thinking\n", get_time() - philo->data->start_time, philo->id);
}

void	sleeeep(t_philo *philo)
{
	printf("%ld %d is sleeping\n", get_time() - philo->data->start_time, philo->id);
	ft_usleep(philo->data->time_to_sleep);
}

void	eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->left_fork->fork);
	pthread_mutex_lock(&philo->data->start_mutex);
	printf("%ld %d has taken a fork\n", get_time() - philo->data->start_time, philo->id);
	pthread_mutex_lock(&philo->right_fork->fork);
	printf("%ld %d has taken a fork\n", get_time() - philo->data->start_time, philo->id);
	printf("%ld %d is eating\n", get_time() - philo->data->start_time, philo->id);
	pthread_mutex_unlock(&philo->data->start_mutex);
	pthread_mutex_lock(&philo->data->meals_mutex);
	philo->last_meal = get_time();
	philo->meals++;
	pthread_mutex_unlock(&philo->data->meals_mutex);
	ft_usleep(philo->data->time_to_eat);
	pthread_mutex_unlock(&philo->left_fork->fork);
	pthread_mutex_unlock(&philo->right_fork->fork);
}

void	*philo_routine(void *arg)
{
	t_philo		*philo;

	philo = (t_philo *)arg;
	// pthread_mutex_lock(&philo->data->start_mutex);
	// while (!philo->data->start_time)
	// {
	// 	pthread_mutex_unlock(&philo->data->start_mutex);
	// 	pthread_mutex_lock(&philo->data->start_mutex);
	// }
	// pthread_mutex_unlock(&philo->data->start_mutex);
	if (philo->id % 2 != 0)
		ft_usleep(philo->data->time_to_eat);
	while (!philo->data->finish)
	{
		eat(philo);
		sleeeep(philo);
		think(philo);
	}
	return (NULL);
}














// if (!philo->meals)
// 	philo->last_meal = philo->data->start_time;
// since = get_time() - philo->last_meal;
// if (since >= (size_t)philo->data->time_to_die)
// 	(printf("%d died!!!!!!!!!!!!!! %ld >= %ld\n",
// 		philo->id, since, philo->data->time_to_die),
// 			philo->data->finish = 1);

// void	eat(t_philo *philo)
// {
// 	t_fork		*first_fork;
// 	t_fork		*second_fork;

// 	if (philo->id % 2 == 0)
// 	{
// 		first_fork = philo->right_fork;
// 		second_fork = philo->left_fork;
// 	}
// 	else
// 	{
// 		first_fork = philo->left_fork;
// 		second_fork = philo->right_fork;
// 	}
// 	pthread_mutex_lock(&first_fork->fork);
// 	pthread_mutex_lock(&second_fork->fork);
// 	printf("%ld %d has taken a fork [%d]\n", philo->data->start_time, philo->id, first_fork->fork_id);
// 	printf("%ld %d has taken a fork [%d]\n", philo->data->start_time, philo->id, first_fork->fork_id);
// 	printf("%ld %d is eating\n", philo->data->start_time, philo->id);
// 	ft_usleep(philo->data->time_to_eat);
// 	printf("%ld %d finished eating\n", philo->data->start_time, philo->id);
// 	pthread_mutex_unlock(&first_fork->fork);
// 	printf("%ld %d released a fork [%d]\n", philo->data->start_time, philo->id, first_fork->fork_id);
// 	pthread_mutex_unlock(&second_fork->fork);
// 	printf("%ld %d released a fork [%d]\n", philo->data->start_time, philo->id, second_fork->fork_id);
// }
// DEBUG
// void	eat(t_philo *philo)
// {
// 	pthread_mutex_lock(&philo->left_fork->fork);
// 	pthread_mutex_lock(&philo->right_fork->fork);
// 	printf("%ld %d has taken a fork [%d]\n", get_time() - philo->data->start_time, philo->id, philo->left_fork->fork_id);
// 	printf("%ld %d has taken a fork [%d]\n", get_time() - philo->data->start_time, philo->id, philo->right_fork->fork_id);
// 	printf("%ld %d is eating\n", get_time() - philo->data->start_time, philo->id);
// 	ft_usleep(philo->data->time_to_eat);
// 	printf("%ld %d finished eating\n", get_time() - philo->data->start_time, philo->id);
// 	pthread_mutex_unlock(&philo->left_fork->fork);
// 	printf("%ld %d released a fork [%d]\n", get_time() - philo->data->start_time, philo->id, philo->left_fork->fork_id);
// 	pthread_mutex_unlock(&philo->right_fork->fork);
// 	printf("%ld %d released a fork [%d]\n", get_time() - philo->data->start_time, philo->id, philo->right_fork->fork_id);
// }