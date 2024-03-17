/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboutsli <yboutsli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 11:01:54 by yboutsli          #+#    #+#             */
/*   Updated: 2024/03/15 16:05:20 by yboutsli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	echo(t_token *token, t_list *list_env, t_list *list_set)
{
	int		i;
	int		j;
	int		nl;
	(void)list_env;
	(void)list_set;

	nl = 1;
	j = 0;
	i = 0;
	if (!token->args)
	{
		printf("\n");
		return (0);
	}
	while (token->args[i])
	{
		j = 0;
		if (token->args[i][j] == '-' && token->args[i][j + 1] == 'n')
		{
			j++;
			while (token->args[i][j] == 'n')
				j++;
			if (token->args[i][j] != '\0')
				break;
			else
				nl = 0;
		}
		else
			break;
		i++;
	}
	while (token->args[i])
	{
		printf("%s", token->args[i]);
		if (token->args[i + 1])
			printf(" ");
		i++;
	}
	if (nl == 1)
		printf("\n");
	return (0);
}
