/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouchta <obouchta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 19:16:46 by obouchta          #+#    #+#             */
/*   Updated: 2024/03/07 20:04:11 by obouchta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	set_valid(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if(i > 0 && str[i] == '=' && str[i + 1] && !ft_isalpha(str[i - 1]))
			return (0);
		i++;
	}
	return (1);
}

int	add_set(t_list **set, char *input)
{
	int	j;
	char *var;
	char *value;

	j = 0;
	while (input[j] && input[j] != '=')
		j++;
	var = ft_substr(input, 0, j);
	value = ft_substr(input, j + 1, ft_strlen(input));
	if (!var || !value)
		return (1);
	ft_lstadd_back_2(set, ft_lstnew_2(var, value));
	free(var);
	free(value);
	return (0);
}