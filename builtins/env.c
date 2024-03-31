/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboutsli <yboutsli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 14:36:05 by yboutsli          #+#    #+#             */
/*   Updated: 2024/03/31 21:47:49 by yboutsli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	env(t_list **list_env, t_cmd *cmd)
{
	t_list	*curr;

	env_lc_update(cmd, list_env);
	if (!list_env)
		return (1);
	curr = *list_env;
	while (curr)
	{
		if (curr->value && curr->type == 0)
			printf("%s=%s\n", curr->var, curr->value);
		curr = curr->next;
	}
	return (0);
}
