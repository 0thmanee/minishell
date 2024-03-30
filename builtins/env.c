/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboutsli <yboutsli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 14:36:05 by yboutsli          #+#    #+#             */
/*   Updated: 2024/03/30 02:45:49 by yboutsli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	env(t_list **list_env, t_cmd *cmd)
{
	t_list	*current;

	env_lc_update(cmd, list_env);
	if (!list_env)
		return (1);
	current = *list_env;
	while (current)
	{
		if (current->value)
			printf("%s=%s\n", current->var, current->value);
		current = current->next;
	}
	return (0);
}
