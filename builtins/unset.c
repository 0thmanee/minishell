/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouchta <obouchta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 21:19:24 by yboutsli          #+#    #+#             */
/*   Updated: 2024/04/04 01:14:21 by obouchta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int unset(t_list **list_env, char **args, t_free **ptrs)
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
				nvalid_output(args[i++], ptrs);
				status = 1;
			}
			else if(!ft_strcmp(current->var, args[i]))
			{
				if (prev)
					prev->next = current->next;
				else
					*list_env = current->next;
				ft_free_ptr(ptrs, current->value);
				ft_free_ptr(ptrs, current->var);
			}
			i++;
		}
		prev = current;
		current = current->next;
	}
	return (status);
}
