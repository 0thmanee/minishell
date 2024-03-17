/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboutsli <yboutsli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 21:19:24 by yboutsli          #+#    #+#             */
/*   Updated: 2024/03/10 21:30:36 by yboutsli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int unset(t_list **list_set, char *var_rm)
{
	t_list *current;
	t_list *prev;

	if (!*list_set)
		return (0);
	current = *list_set;
	prev = NULL;
	while (current)
	{
		if (!ft_strcmp(current->var, var_rm))
		{
			if (prev)
				prev->next = current->next;
			else
				*list_set = current->next;
			free(current->value);
			free(current->var);
			return (0);
		}
		prev = current;
		current = current->next;
	}
	return (1);
}
