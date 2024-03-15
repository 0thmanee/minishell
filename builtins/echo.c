/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboutsli <yboutsli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 11:01:54 by yboutsli          #+#    #+#             */
/*   Updated: 2024/03/15 00:26:38 by yboutsli         ###   ########.fr       */
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
	// if (str[0] == '$' && str[1])
	// {
	// 	str++;
	// 	env_value = get_env(&env, str);
	// 	set_value = get_env(&set, str);
	// 	if (!env_value && !set_value)
	// 		str = "";
	// 	else if (!env_value)
	// 		str = set_value;
	// 	else
	// 		str = env_value;	
	// 	echo(str, nl, env, set);
	// }
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
