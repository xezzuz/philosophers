/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nazouz <nazouz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 11:02:15 by nazouz            #+#    #+#             */
/*   Updated: 2024/03/29 00:54:01 by nazouz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers_bonus.h"

int	ft_atoi(const char *str)
{
	int				sign;
	long			result;

	sign = 1;
	result = 0;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	if (!(*str) || sign == -1)
		return (-1);
	while (*str >= 48 && *str <= 57)
	{
		result = result * 10 + (*str++ - 48);
		if (result > INT_MAX)
			return (-1);
	}
	if (*str)
		return (-1);
	return (result * sign);
}
