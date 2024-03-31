/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils_1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboutsli <yboutsli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 14:59:37 by yboutsli          #+#    #+#             */
/*   Updated: 2024/03/31 05:50:49 by yboutsli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free(char **tab)
{
	int	i;

	i = 0;
	while (tab && tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

char	**path(t_list **envp)
{
	char	**npath;
	t_list	*current;

	current = *envp;
	while (current)
	{
		if (!ft_strcmp(current->var, "PATH"))
		{
			npath = ft_split(current->value, ':');
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
char	**list2tab(t_list *list_env)
{
	char 	**tab;
	t_list *current;
	char	*tmp2;
	int		i;
	char	*tmp1;

	tab = malloc((env_size(list_env) + 1) * sizeof(char *));
	if (!tab)
		return (NULL);
	current = list_env;
	i = 0;
	while (current)
	{
		if (current->var && current->value)
		{
			tmp1 = ft_strjoin_2(current->var, "=");
			tmp2 = ft_strjoin_2(tmp1, current->value);
			free(tmp1);
			tab[i] = malloc((ft_strlen(tmp2) + 1));
			if (!tab[i])
				return (NULL);
			ft_strcpy(tab[i], tmp2);
			i++;
		}
		current = current->next;
	}
	tab[i] = NULL;
	return(tab);
}
