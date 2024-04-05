/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboutsli <yboutsli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 11:01:54 by yboutsli          #+#    #+#             */
/*   Updated: 2024/04/05 17:30:03 by yboutsli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	echo_utils(t_cmd *cmd, int *i)
{
	printf("%s", cmd->args[*i]);
	if (cmd->args[(*i) + 1])
		printf(" ");
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
		printf("\n");
}

int	echo(t_cmd *cmd)
{
	int		i;
	int		j;
	int		nl;

	echo_init(&nl, &j, &i);
	if (!cmd->args)
		return (printf("\n"), 0);
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
