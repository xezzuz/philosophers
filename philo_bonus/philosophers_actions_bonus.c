/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_actions_bonus.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nazouz <nazouz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 10:39:29 by nazouz            #+#    #+#             */
/*   Updated: 2024/03/25 02:09:58 by nazouz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

void	print_state(sem_t *write, int philo_id, char *state, size_t elapsed)
{
	sem_wait(write);
	printf("%ld %d %s\n", elapsed, philo_id, state);
	if (ft_strcmp(state, "died"))
		sem_post(write);
}

void	sleeeep(t_philo *philo)
{
	print_state(philo->data->write, philo->id,
		SLEEPING, get_time() - philo->data->start_time);
	ft_usleep(philo->data->t_sleep);
}

void	eat(t_philo *philo)
{
	if (!philo->data->max_meals)
		exit(0);
	sem_wait(philo->data->forks);
	print_state(philo->data->write, philo->id,
		PICK_UP, get_time() - philo->data->start_time);
	sem_wait(philo->data->forks);
	print_state(philo->data->write, philo->id,
		PICK_UP, get_time() - philo->data->start_time);
	sem_wait(philo->data->lock);
	philo->death_date = get_time() + philo->data->t_die;
	philo->meals++;
	sem_post(philo->data->lock);
	print_state(philo->data->write, philo->id,
		EATING, get_time() - philo->data->start_time);
	ft_usleep(philo->data->t_eat);
	sem_post(philo->data->forks);
	sem_post(philo->data->forks);
}
