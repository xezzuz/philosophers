/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nazouz <nazouz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 10:49:21 by nazouz            #+#    #+#             */
/*   Updated: 2024/03/03 11:55:20 by nazouz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	only_nums(char **argv)
{
	int		i;
	int		j;

	i = 1;
	while (argv[i])
	{
		j = 0;
		while (argv[i][j] == 32 || (argv[i][j] >=9 && argv[i][j] <= 13))
			j++;
		while (argv[i][j])
		{
			if (argv[i][j] < '0' || argv[i][j] > '9')
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

int	parse(t_data *data, char **argv)
{
	if (!only_nums(argv))
		return (0);
	data->philos_nbr = ft_atoll(argv[1]);
	data->t_die = ft_atoll(argv[2]);
	data->t_eat = ft_atoll(argv[3]);
	data->t_sleep = ft_atoll(argv[4]);
	if (!argv[5])
		data->max_meals = -1;
	else
		data->max_meals = ft_atoll(argv[5]);
	data->stuffed_philos = 0;
	data->start_time = 0;
	data->finish_sim = 0;
	return (1);
}
