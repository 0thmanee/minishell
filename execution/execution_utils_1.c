/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils_1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboutsli <yboutsli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 14:59:37 by yboutsli          #+#    #+#             */
/*   Updated: 2024/03/14 15:00:03 by yboutsli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
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