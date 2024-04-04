/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouchta <obouchta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 14:36:05 by yboutsli          #+#    #+#             */
/*   Updated: 2024/04/04 01:47:49 by obouchta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	env(t_list **list_env, t_cmd *cmd, t_free **ptrs)
{
	t_list	*curr;

	env_lc_update(cmd, list_env, ptrs);
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
