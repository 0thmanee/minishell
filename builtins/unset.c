/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboutsli <yboutsli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 21:19:24 by yboutsli          #+#    #+#             */
/*   Updated: 2024/04/26 16:34:27 by yboutsli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	unset_utils(t_list **env, t_list *c, t_list *p, t_free **ptrs)
{
	if (p)
		p->next = c->next;
	else
		*env = c->next;
	ft_free_ptr(ptrs, c->value);
	ft_free_ptr(ptrs, c->var);
}

void	unset_utils1(t_list **curr, t_list **prev, t_list **list_env)
{
	*curr = *list_env;
	*prev = NULL;
}

void	unset_utils2(t_list **curr, t_list **prev)
{
	*prev = *curr;
	(*curr) = (*curr)->next;
}

static int	unset_valid(char *str)
{
	int	i;

	i = 0;
	if (ft_isalpha(str[0]) && str[0] != '_')
		return (1);
	while (str[i] != '\0')
	{
		if ((ft_isalpha(str[i]) && ft_isdigit(str[i])) && str[i] != '_')
			return (1);
		i++;
	}
	return (0);
}

int	unset(t_list **list_env, char **args, t_free **ptrs)
{
	t_list	*curr;
	t_list	*prev;
	int		i;
	int		status;

	status = 0;
	if (!*list_env || !args)
		return (0);
	i = -1;
	while (args[++i])
	{
		unset_utils1(&curr, &prev, list_env);
		while (curr)
		{
			if (unset_valid(args[i]))
			{
				status = nvalid_output(args[i], "unset");
				break ;
			}
			else if (!ft_strcmp(curr->var, args[i]))
				unset_utils(list_env, curr, prev, ptrs);
			unset_utils2(&curr, &prev);
		}
	}
	return (status);
}
