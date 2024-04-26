/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouchta <obouchta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 11:01:54 by yboutsli          #+#    #+#             */
/*   Updated: 2024/04/26 15:32:11 by obouchta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	echo_utils(t_cmd *cmd, int *i)
{
	ft_putstr_fd(cmd->args[*i], 1);
	if (cmd->args[(*i) + 1])
		ft_putstr_fd(" ", 1);
	(*i)++;
}

static void	echo_init(int *nl, int *j, int *i)
{
	*nl = 1;
	*j = 0;
	*i = -1;
}

static void	echo_utils1(t_cmd *cmd, int i, int nl)
{
	while (cmd->args[i])
		echo_utils(cmd, &i);
	if (nl == 1)
		ft_putstr_fd("\n", 1);
}

int	echo(t_cmd *cmd)
{
	int		i;
	int		j;
	int		nl;

	echo_init(&nl, &j, &i);
	if (!cmd->args)
		return (ft_putstr_fd("\n", 1), 0);
	while (cmd->args[++i])
	{
		j = 0;
		if (cmd->args[i][j] == '-' && cmd->args[i][j + 1] == 'n')
		{
			j++;
			while (cmd->args[i][j] == 'n')
				j++;
			if (cmd->args[i][j] != '\0')
				break ;
			else
				nl = 0;
		}
		else
			break ;
	}
	echo_utils1(cmd, i, nl);
	return (0);
}
