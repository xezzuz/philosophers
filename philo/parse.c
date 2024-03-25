/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nazouz <nazouz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 10:49:21 by nazouz            #+#    #+#             */
/*   Updated: 2024/03/25 05:17:15 by nazouz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	only_nums(char **argv)
{
	int		i;

	i = 1;
	while (argv[i])
	{
		if (ft_atoi(argv[i]) <= -1)
			return (0);
		i++;
	}
	return (1);
}

int	parse(t_data *data, char **argv)
{
	if (!only_nums(argv))
		return (0);
	data->philos_nbr = ft_atoi(argv[1]);
	data->t_die = ft_atoi(argv[2]);
	data->t_eat = ft_atoi(argv[3]);
	data->t_sleep = ft_atoi(argv[4]);
	if (!argv[5])
		data->max_meals = -1;
	else
		data->max_meals = ft_atoi(argv[5]);
	data->start_time = 0;
	data->dead = 0;
	return (1);
}
