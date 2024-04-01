/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouchta <obouchta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 22:45:14 by obouchta          #+#    #+#             */
/*   Updated: 2024/03/31 22:45:28 by obouchta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

long	calc_result(long tmp, long result, char c, int sign)
{
	tmp = (result * 10) + (c - 48);
	if (tmp < result && sign == 1)
		return (-1);
	else if (tmp < result && sign == -1)
		return (0);
	return (tmp);
}

int	ft_atoi(const char *str)
{
	int		i;
	int		sign;
	long	result;
	long	tmp;

	i = 0;
	sign = 1;
	result = 0;
	tmp = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i] && str[i] >= '0' && str[i] <= '9')
	{
		result = calc_result(tmp, result, str[i], sign);
		i++;
	}
	return (sign * result);
}