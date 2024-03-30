/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboutsli <yboutsli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 21:19:24 by yboutsli          #+#    #+#             */
/*   Updated: 2024/03/30 01:59:08 by yboutsli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int unset(t_list **list_env, char **args)
{
	t_list *current;
	t_list *prev;
	int		i;
	int		status;

	status = 0;
	if (!*list_env || !args)
		return (0);
	current = *list_env;
	prev = NULL;
	
	while (current)
	{
		i = 0;
		while (args[i])
		{
			if (valid(args[i]))
			{
				nvalid_output(args[i++]);
				status = 1;
			}
			else if(!ft_strcmp(current->var, args[i]))
			{
				if (prev)
					prev->next = current->next;
				else
					*list_env = current->next;
				free(current->value);
				free(current->var);
			}
			i++;
		}
		prev = current;
		current = current->next;
	}
	return (status);
}
