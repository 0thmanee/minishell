/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouchta <obouchta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 14:59:37 by yboutsli          #+#    #+#             */
/*   Updated: 2024/04/14 16:48:23 by obouchta         ###   ########.fr       */
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

static void	index_init(int *i, t_list **list_env, t_list **current,
	t_free **ptrs)
{
	char	*tmp;

	i[0] = 0;
	i[1] = 0;
	tmp = get_env(list_env, "SHLVL", 0, ptrs);
	if (!tmp)
		i[1] = 1;
	*current = *list_env;
}

static char	*list2tab_1(char *value, t_free **ptrs, char *tmp0)
{
	int		shlvl;
	char	*str_shlvl;
	char	*tmp1;

	shlvl = ft_atoi(value) + 1;
	ft_free_ptr(ptrs, value);
	str_shlvl = int_to_str(shlvl, ptrs);
	tmp1 = ft_strjoin(tmp0, str_shlvl, ptrs);
	ft_free_ptr(ptrs, str_shlvl);
	return (tmp1);
}

static void	creat_tabs(char **tab, t_free **ptrs, char *tmp1)
{
	*tab = ft_malloc(ptrs, (ft_strlen(tmp1) + 1));
	ft_strcpy(*tab, tmp1);
	ft_free_ptr(ptrs, tmp1);
}

char	**list2tab(t_list *list_env, t_free **ptrs, int type)
{
	char	**tab;
	t_list	*current;
	char	*tmp[2];
	int		i[2];

	index_init(i, &list_env, &current, ptrs);
	tab = ft_malloc(ptrs, (env_size(list_env) + 1 + i[1]) * sizeof(char *));
	while (current)
	{
		if (current->var && current->value)
		{
			tmp[0] = ft_strjoin(current->var, "=", ptrs);
			if (!ft_strcmp(current->var, "SHLVL") && type == 1)
				tmp[1] = list2tab_1(current->value, ptrs, tmp[0]);
			else
				tmp[1] = ft_strjoin(tmp[0], current->value, ptrs);
			ft_free_ptr(ptrs, tmp[0]);
			creat_tabs(&tab[i[0]], ptrs, tmp[1]);
			i[0]++;
		}
		current = current->next;
	}
	if (i[1] == 1)
		tab[i[0]++] = ft_strdup("SHLVL=1", ptrs);
	return (tab[i[0]] = NULL, tab);
}
