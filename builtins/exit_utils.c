/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboutsli <yboutsli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 16:17:59 by yboutsli          #+#    #+#             */
/*   Updated: 2024/04/23 14:03:01 by yboutsli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	long_nb(char *s)
{
	size_t		nb;
	size_t		nb2;
	int			sign;
	int			i;

	nb = 0;
	sign = 1;
	i = 0;
	if (s[i] == '-' || s[i] == '+')
	{
		if (s[i] == '-')
			sign = -1;
		i++;
	}
	while (s[i])
	{
		nb = (nb * 10) + (s[i] - 48);
		if ((sign == 1 && nb > (size_t)LLONG_MAX)
			|| (sign == -1 && nb > ((size_t)(LLONG_MAX) + 1))
			|| (nb < nb2))
			return (1);
		nb2 = nb;
		i++;
	}
	return (0);
}

static void	error_msg(char *str, t_free **ptrs)
{
	ft_putstr_fd("exit\nminishell: exit: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": numeric argument required\n", 2);
	ft_free_all(ptrs);
	exit (255);
}

int	valid_args(char **args, t_free **ptrs)
{
	int	i;
	int	j;

	i = -1;
	while (args[++i])
	{
		if (i > 0)
		{
			ft_putstr_fd("exit\n", 2);
			ft_putstr_fd("minishel: exit: too many arguments\n", 2);
			return (1);
		}
		j = -1;
		if ((args[i][0] == '-' || args[i][0] == '+') && args[i][1] != '\0')
			j++;
		while (args[i][++j])
		{
			if (ft_isdigit(args[i][j]))
				error_msg(args[i], ptrs);
		}
		if (long_nb(args[i]))
			error_msg(args[i], ptrs);
	}
	return (0);
}
