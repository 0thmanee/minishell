/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouchta <obouchta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 00:17:09 by yboutsli          #+#    #+#             */
/*   Updated: 2024/04/01 01:16:08 by obouchta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
void	error_msg(char *str)
{
	ft_putstr_fd("exit\nminishell: exit: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": numeric argument required\n", 2);
	exit (255);
}

long	atoi_long(char *str)
{
	long long	nb;
	int		sign;
	int		i;

	nb = 0;
	sign = 1;
	i = 0;
	if (str[i] == '-')
	{
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
int	long_nb(char *s)
{
	long long	nb;
	int		sign;
	int		i;

	nb = 0;
	sign = 1;
	i = 0;
	if (s[i] == '-')
	{
		sign = -1;
		i++;
	}
	while (s[i])
	{
		nb = (nb * 10) + (s[i] - 48);
		if ((nb * sign) > LONG_MAX || (nb * sign) < LONG_MIN)
			return (1);
		i++;
	}
	return (0);
}

int	valid_args(char **args)
{
	int	i;
	int	j;

	i = -1;
	while(args[++i])
	{
		if (i > 0)
		{
			ft_putstr_fd("exit\n", 2);
			ft_putstr_fd("minishel: exit: too many arguments\n", 2);
			return (1);
		}
		j = -1;
		if (args[i][0] == '-' && args[i][1] != '\0')
			j++;
		while (args[i][++j])		
		{
			if (ft_isdigit(args[i][j]))
				error_msg(args[i]);
		}
		if (long_nb(args[i]))
			error_msg(args[i]);
	}
	return (0);
}
void	ft_exit_utils(char *arg)
{
	long nb;

	nb = atoi_long(arg);
	//ft_free
	exit(nb);
}
int	ft_exit(t_cmd *cmd, t_list **list_env)
{
	if (!cmd->args)
		exit(ft_atoi(get_env(list_env, "?")));//free
	else if (valid_args(cmd->args))
		return (1);
	else
		ft_exit_utils(cmd->args[0]);
	return (0);
}