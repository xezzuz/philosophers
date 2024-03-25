/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nazouz <nazouz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 11:02:15 by nazouz            #+#    #+#             */
/*   Updated: 2024/03/25 05:13:06 by nazouz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers_bonus.h"

int	ft_atoi(const char *str)
{
	int				sign;
	long			result;
	long			resulttemp;

	sign = 1;
	result = 0;
	resulttemp = 0;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str >= 48 && *str <= 57)
	{
		result = resulttemp * 10 + (*str++ - 48);
		if (result < resulttemp)
			return (-1);
		resulttemp = result;
	}
	if (*str)
		return (-1);
	return (result * sign);
}
