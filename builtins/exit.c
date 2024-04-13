/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouchta <obouchta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 00:17:09 by yboutsli          #+#    #+#             */
/*   Updated: 2024/04/13 20:33:47 by obouchta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

long long	atoi_long(char *str)
{
	long long	nb;
	int			sign;
	int			i;

	nb = 0;
	sign = 1;
	i = 0;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i])
	{
		nb = (nb * 10) + (str[i] - 48);
		i++;
	}
	return (nb * sign);
}

void	ft_exit_utils(char *arg, t_free **ptrs)
{
	long	nb;

	nb = atoi_long(arg);
	printf("exit\n");
	ft_free_all(ptrs);
	exit(nb);
}

int	ft_exit(t_cmd *cmd, t_list **list_env, t_free **ptrs, int exit_print)
{
	int	exit_stat;

	if (!cmd->args)
	{
		exit_stat = ft_atoi(get_env(list_env, "?"));
		if (exit_print)
			printf("exit\n");
		ft_free_all(ptrs);
		exit(exit_stat);
	}
	else if (valid_args(cmd->args, ptrs))
		return (1);
	else
		ft_exit_utils(cmd->args[0], ptrs);
	return (0);
}
