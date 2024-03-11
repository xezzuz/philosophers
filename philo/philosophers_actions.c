/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_actions.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nazouz <nazouz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 10:39:29 by nazouz            #+#    #+#             */
/*   Updated: 2024/03/11 15:15:33 by nazouz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	print_state(t_data *data, int philo_id, int state)
{
	long		elapsed;

	if (!a_philo_died(data) || state == DIED)
	{
		elapsed = get_time() - data->start_time;
		pthread_mutex_lock(&data->write);
		if (state == PICK_UP)
			printf("%ld %d has taken a fork\n", elapsed, philo_id);
		else if (state == EATING)
			printf("%ld %d is eating\n", elapsed, philo_id);
		else if (state == SLEEPING)
			printf("%ld %d is sleeping\n", elapsed, philo_id);
		else if (state == THINKING)
			printf("%ld %d is thinking\n", elapsed, philo_id);
		else if (state == DIED)
			printf("%ld %d died\n", elapsed, philo_id);
		pthread_mutex_unlock(&data->write);
	}
}

void	forks(t_philo *philo, int to_do)
{
	if (to_do == PICK_UP)
	{
		pthread_mutex_lock(&philo->left_fork->fork);
		print_state(philo->data, philo->id, PICK_UP);
		pthread_mutex_lock(&philo->right_fork->fork);
		print_state(philo->data, philo->id, PICK_UP);
	}
	else if (to_do == PUT_DOWN)
	{
		pthread_mutex_unlock(&philo->left_fork->fork);
		pthread_mutex_unlock(&philo->right_fork->fork);
	}
}

void	sleeeep(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->lock);
	if (philo->data->dead)
	{
		pthread_mutex_unlock(&philo->data->lock);
		return ;
	}
	pthread_mutex_unlock(&philo->data->lock);
	print_state(philo->data, philo->id, SLEEPING);
	ft_usleep(philo->data->t_sleep);
}

void	eat(t_philo *philo)
{
	if (!philo->data->max_meals)
		return ;
	forks(philo, PICK_UP);
	pthread_mutex_lock(&philo->data->lock);
	philo->death_date = get_time() + philo->data->t_die;
	pthread_mutex_unlock(&philo->data->lock);
	print_state(philo->data, philo->id, EATING);
	ft_usleep(philo->data->t_eat);
	pthread_mutex_lock(&philo->data->lock);
	philo->meals++;
	pthread_mutex_unlock(&philo->data->lock);
	forks(philo, PUT_DOWN);
}
