/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_actions_bonus.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nazouz <nazouz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 10:39:29 by nazouz            #+#    #+#             */
/*   Updated: 2024/03/15 21:26:22 by nazouz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

void	print_state(t_philo *philo, int philo_id, int state)
{
	long		elapsed;

	elapsed = get_time() - philo->data->start_time;
	sem_wait(philo->data->write);
	if (state == PICK_UP)
		printf("%ld %d has taken a fork\n", elapsed, philo_id);
	else if (state == EATING)
		printf("%ld %d is eating\n", elapsed, philo_id);
	else if (state == SLEEPING)
		printf("%ld %d is sleeping\n", elapsed, philo_id);
	else if (state == THINKING)
		printf("%ld %d is thinking\n", elapsed, philo_id);
	else if (state == DIED)
	{
		printf("%ld %d died\n", elapsed, philo_id);
		return ;
	}
	sem_post(philo->data->write);
}

void	forks(t_philo *philo, int to_do)
{
	if (to_do == PICK_UP)
	{
		sem_wait(philo->data->forks);
		print_state(philo, philo->id, PICK_UP);
		sem_wait(philo->data->forks);
		print_state(philo, philo->id, PICK_UP);
	}
	else if (to_do == PUT_DOWN)
	{
		sem_post(philo->data->forks);
		sem_post(philo->data->forks);
	}
}

void	sleeeep(t_philo *philo)
{
	print_state(philo, philo->id, SLEEPING);
	ft_usleep(philo->data->t_sleep);
}

void	eat(t_philo *philo)
{
	if (!philo->data->max_meals)
		return ;
	forks(philo, PICK_UP);
	sem_wait(philo->lock);
	philo->death_date = get_time() + philo->data->t_die;
	sem_post(philo->lock);
	print_state(philo, philo->id, EATING);
	ft_usleep(philo->data->t_eat);
	sem_wait(philo->lock);
	philo->meals++;
	sem_post(philo->lock);
	forks(philo, PUT_DOWN);
}
