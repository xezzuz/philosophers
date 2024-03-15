/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nazouz <nazouz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 08:59:13 by nazouz            #+#    #+#             */
/*   Updated: 2024/03/15 02:46:47 by nazouz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_clean(t_data *data)
{
	int			i;

	i = 0;
	while (i < data->philos_nbr)
	{
		sem_close(data->philos[i].lock);
		sem_unlink(data->philos[i].lock_str);
		free(data->philos[i++].lock_str);
	}
	sem_close(data->forks);
	sem_unlink("/forks");
	sem_close(data->write);
	sem_unlink("/write");
	free(data->philos);
}

size_t	get_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		write(2, "gettimeofday() error\n", 22);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

int	ft_usleep(size_t milliseconds)
{
	size_t	start;

	start = get_time();
	while ((get_time() - start) < milliseconds)
		usleep(500);
	return (0);
}
