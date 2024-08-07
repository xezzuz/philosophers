/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nazouz <nazouz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 08:59:13 by nazouz            #+#    #+#             */
/*   Updated: 2024/03/25 05:31:23 by nazouz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_clean(t_data *data, int error)
{
	int			i;

	if (error == ENOTHD)
		ft_putstr_fd("pthread_create() failed\n", STDERR_FILENO);
	i = 0;
	while (i < data->philos_nbr)
		pthread_mutex_destroy(&data->forks[i++].fork);
	pthread_mutex_destroy(&data->lock);
	pthread_mutex_destroy(&data->write);
	free(data->philos);
	free(data->forks);
}

size_t	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

int	ft_usleep(size_t ms)
{
	size_t	start;

	start = get_time();
	while ((get_time() - start) < ms)
		usleep(100);
	return (0);
}
