/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouchta <obouchta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 00:17:09 by yboutsli          #+#    #+#             */
/*   Updated: 2024/04/04 02:59:06 by obouchta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
void	error_msg(char *str, t_free **ptrs)
{
	ft_putstr_fd("exit\nminishell: exit: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": numeric argument required\n", 2);
	ft_free_all(ptrs);
	exit (255);
}

long long	atoi_long(char *str)
{
	long long	nb;
	int		sign;
	int		i;

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

int	long_nb(char *s)
{
	unsigned long long	nb;
	int					sign;
	int					i;

	(nb = 0, sign = 1, i = 0);
	if (s[i] == '-' || s[i] == '+')
	{
		if (s[i] == '-')
			sign = -1;
		i++;
	}
	while (s[i])
	{
		nb = (nb * 10) + (s[i] - 48);
		if ((sign == 1 && nb > LLONG_MAX)
			|| (sign == -1 && nb > (unsigned long long)LLONG_MAX + 1))
			return (1);
		i++;
	}
	return (0);
}

int	valid_args(char **args, t_free **ptrs)
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
void	ft_exit_utils(char *arg, t_free **ptrs)
{
	long nb;

	nb = atoi_long(arg);
	printf("exit\n");
	ft_free_all(ptrs);
	exit(nb);
}

int	ft_exit(t_cmd *cmd, t_list **list_env, t_free **ptrs)
{
	int	exit_stat;
	if (!cmd->args)
	{
		exit_stat = ft_atoi(get_env(list_env, "?"));
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