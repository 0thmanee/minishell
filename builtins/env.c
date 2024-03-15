/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouchta <obouchta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 14:36:05 by yboutsli          #+#    #+#             */
/*   Updated: 2024/03/15 02:11:29 by obouchta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	env(t_list *list_env)
{
	t_list	*current;

	if (!list_env)
		return (1);
	current = list_env;
	while (current)
	{
		printf("%s=%s\n", current->var, current->value);
		current = current->next;
	}
	return (0);
}
