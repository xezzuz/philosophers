/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nazouz <nazouz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 10:42:16 by nazouz            #+#    #+#             */
/*   Updated: 2024/03/02 10:52:19 by nazouz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

size_t	get_time(void)
{
	struct timeval time;

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

int main(int argc, char **argv)
{
	t_data		data;

	if (argc != 5 && argc != 6)
		return (ft_putstr_fd("Invalid input!\n", 2), 1);
	if (!parse(&data, argv))
		return (ft_putstr_fd("Invalid input!\n", 2), 1);
	t_data_init(&data);
}
