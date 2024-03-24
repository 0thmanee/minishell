/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboutsli <yboutsli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 11:01:54 by yboutsli          #+#    #+#             */
/*   Updated: 2024/03/24 16:24:42 by yboutsli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	echo(t_cmd *cmd)
{
	int		i;
	int		j;
	int		nl;

	nl = 1;
	j = 0;
	i = 0;
	if (!cmd->args)
	{
		printf("\n");
		return (0);
	}
	while (cmd->args[i])
	{
		j = 0;
		if (cmd->args[i][j] == '-' && cmd->args[i][j + 1] == 'n')
		{
			j++;
			while (cmd->args[i][j] == 'n')
				j++;
			if (cmd->args[i][j] != '\0')
				break;
			else
				nl = 0;
		}
		else
			break;
		i++;
	}
	while (cmd->args[i])
	{
		printf("%s", cmd->args[i]);
		if (cmd->args[i + 1])
			printf(" ");
		i++;
	}
	if (nl == 1)
		printf("\n");
	return (0);
}
