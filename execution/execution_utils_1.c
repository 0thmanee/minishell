/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils_1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouchta <obouchta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 14:59:37 by yboutsli          #+#    #+#             */
/*   Updated: 2024/04/04 01:48:25 by obouchta         ###   ########.fr       */
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

char	**path(t_list **envp, t_free **ptrs)
{
	char	**npath;
	t_list	*current;

	current = *envp;
	while (current)
	{
		if (!ft_strcmp(current->var, "PATH"))
		{
			npath = ft_split(current->value, ':', ptrs);
			return (npath);
		}
		current = current->next;
	}
	return (NULL);
}
void	close2(int tab[2])
{
	close(tab[0]);
	close(tab[1]);
}
char	**list2tab(t_list *list_env, t_free **ptrs)
{
	char 	**tab;
	t_list *current;
	char	*tmp2;
	int		i;
	char	*tmp1;

	tab = ft_malloc(ptrs, (env_size(list_env) + 1) * sizeof(char *));
	current = list_env;
	i = 0;
	while (current)
	{
		if (current->var && current->value)
		{
			tmp1 = ft_strjoin(current->var, "=", ptrs);
			tmp2 = ft_strjoin(tmp1, current->value, ptrs);
			ft_free_ptr(ptrs, tmp1);
			tab[i] = ft_malloc(ptrs, (ft_strlen(tmp2) + 1));
			ft_strcpy(tab[i], tmp2);
			i++;
		}
		current = current->next;
	}
	tab[i] = NULL;
	return(tab);
}
