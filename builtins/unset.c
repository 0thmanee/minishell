/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboutsli <yboutsli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 21:19:24 by yboutsli          #+#    #+#             */
/*   Updated: 2024/04/05 02:11:08 by yboutsli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int unset(t_list **list_env, char **args, t_free **ptrs)
{
	t_list *curr;
	t_list *prev;
	int		i;
	int		status;

	status = 0;
	if (!*list_env || !args)
		return (0);
	i = -1;
	while (args[++i])
	{
		curr = *list_env;
		prev = NULL; 
		while (curr)
		{
			if (valid(args[i]))
			{
				nvalid_output(args[i], "unset");
				status = 1;
				break;
			}
			else if(!ft_strcmp(curr->var, args[i]))
			{
				if (prev)
					prev->next = curr->next;
				else
					*list_env = curr->next;
				ft_free_ptr(ptrs, curr->value);
				ft_free_ptr(ptrs, curr->var);
			}
			prev = curr;
			curr = curr->next;
		}
	}
	return (status);
}
