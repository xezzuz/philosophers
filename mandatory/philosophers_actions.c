/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_actions.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nazouz <nazouz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 10:39:29 by nazouz            #+#    #+#             */
/*   Updated: 2024/03/03 18:04:31 by nazouz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	print_state(t_philo *philo, int state)
{
	long		elapsed;

	elapsed = get_time() - philo->data->start_time;
	pthread_mutex_lock(&philo->data->write);
	if (state == PICK_UP)
		printf("%ld %d has taken a fork\n", elapsed, philo->id);
	else if (state == EATING)
		printf("%ld %d is eating\n", elapsed, philo->id);
	else if (state == SLEEPING)
		printf("%ld %d is sleeping\n", elapsed, philo->id);
	else if (state == THINKING)
		printf("%ld %d is thinking\n", elapsed, philo->id);
	else if (state == DIED)
		printf("%ld %d died\n", elapsed, philo->id);
	pthread_mutex_unlock(&philo->data->write);
}

void	forks(t_philo *philo, int to_do)
{
	if (to_do == PICK_UP)
	{
		pthread_mutex_lock(&philo->left_fork->fork);
		print_state(philo, PICK_UP);
		pthread_mutex_lock(&philo->right_fork->fork);
		print_state(philo, PICK_UP);
	}
	else if (to_do == PUT_DOWN)
	{
		pthread_mutex_unlock(&philo->left_fork->fork);
		pthread_mutex_unlock(&philo->right_fork->fork);	
	}
}

void	sleeeep(t_philo *philo)
{
	print_state(philo, SLEEPING);
	ft_usleep(philo->data->t_sleep);
}

void	eat(t_philo *philo)
{
	// pthread_mutex_lock(&philo->lock);
	forks(philo, PICK_UP);
	// update death date
	pthread_mutex_lock(&philo->lock);
	philo->death_date = get_time() + philo->data->t_die;
	pthread_mutex_unlock(&philo->lock);
	print_state(philo, EATING);
	// ft_usleep
	ft_usleep(philo->data->t_eat);
	// increment meals
	pthread_mutex_lock(&philo->lock);
	philo->meals++;
	pthread_mutex_unlock(&philo->lock);
	if (philo->meals == philo->data->max_meals)
		philo->stuffed = 1;
	forks(philo, PUT_DOWN);
	// pthread_mutex_unlock(&philo->lock);
}
