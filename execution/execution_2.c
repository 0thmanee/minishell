/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouchta <obouchta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 14:59:37 by yboutsli          #+#    #+#             */
/*   Updated: 2024/04/19 19:42:18 by obouchta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free(char **tab, t_free **ptrs)
{
	int	i;

	i = 0;
	while (tab && tab[i])
	{
		ft_free_ptr(ptrs, tab[i]);
		i++;
	}
	ft_free_ptr(ptrs, tab);
}

static void	creat_tabs(char **tab, t_free **ptrs, char *tmp1)
{
	*tab = ft_malloc(ptrs, (ft_strlen(tmp1) + 1));
	ft_strcpy(*tab, tmp1);
	ft_free_ptr(ptrs, tmp1);
}

char	**list2tab(t_list *list_env, t_free **ptrs)
{
	char	**tab;
	t_list	*curr;
	char	*tmp[2];
	int		i;

	if (!list_env)
		return (NULL);
	i = 0;
	tab = ft_malloc(ptrs, (env_size(list_env) + 1) * sizeof(char *));
	curr = list_env;
	while (curr)
	{
		if (curr->var && curr->value && curr->type == 0)
		{
			tmp[0] = ft_strjoin(curr->var, "=", ptrs);
			tmp[1] = ft_strjoin(tmp[0], curr->value, ptrs);
			(ft_free_ptr(ptrs, tmp[0]), creat_tabs(&tab[i++], ptrs, tmp[1]));
		}
		curr = curr->next;
	}
	return (tab[i] = NULL, tab);
}
