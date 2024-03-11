/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nazouz <nazouz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 10:42:16 by nazouz            #+#    #+#             */
/*   Updated: 2024/03/11 19:26:46 by nazouz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int argc, char **argv)
{
	t_data		data;

	if (argc != 5 && argc != 6)
		return (ft_putstr_fd("Invalid input!\n", 2), 1);
	if (!parse(&data, argv))
		return (ft_putstr_fd("Invalid input!\n", 2), 1);
	if (t_data_init(&data))
		return (1);
	if (philosophers(&data))
		return (ft_clean(&data, ENOTHD), 1);
	return (ft_clean(&data, 0), 0);
}
