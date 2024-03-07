/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouchta <obouchta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 11:01:54 by yboutsli          #+#    #+#             */
/*   Updated: 2024/03/07 19:50:41 by obouchta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	echo(char *str, int nl, t_list *env, t_list *set)
{
	char	*env_value;
	char	*set_value;

	if (str[0] == '$' && str[1])
	{
		str++;
		env_value = get_env(&env, str);
		set_value = get_env(&set, str);
		if (!env_value && !set_value)
			str = "";
		else if (!env_value)
			str = set_value;
		else
			str = env_value;	
		echo(str, nl, env, set);
	}
	else if (nl == 1)
		printf("|%s|\n", str);
	else
		printf("|%s|", str);
	return (0);
}
