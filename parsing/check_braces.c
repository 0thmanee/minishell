/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_braces.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouchta <obouchta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 04:48:49 by obouchta          #+#    #+#             */
/*   Updated: 2024/04/19 16:47:39 by obouchta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_braces_helper(char *value, int *i)
{
	while (value[*i] && value[*i] != '}' && value[*i] != '\"')
	{
		if (char_is_valid(value[*i]) && value[*i + 1]
			&& !char_is_valid(value[*i + 1]))
			return (1);
		if (is_whitespace(value[*i])
			|| (char_is_valid(value[*i]) && value[*i] != '?')
			|| value[*i] == '{' || value[(*i)++] == '$')
			return (1);
	}
	if (value[*i] != '}')
		return (1);
	return (0);
}

int	check_braces(char *value)
{
	int	i;

	i = 0;
	while (value[i])
	{
		if ((quoted(value, i) == '\"' || !quoted(value, i))
			&& value[i] == '$' && value[i + 1] && value[i + 1] == '{')
		{
			i += 2;
			if (!value[i] || value[i] == '{' || value[i] == '}'
				|| value[i] == '\"')
				return (1);
			else
			{
				if (check_braces_helper(value, &i))
					return (1);
			}
			continue ;
		}
		i++;
	}
	return (0);
}

int	invalid_braces(t_token *curr)
{
	int	i;

	i = 0;
	if (curr->value && ft_strchr(curr->value, '{')
		&& check_braces(curr->value))
		return (1);
	if (curr->args_len)
	{
		while (i < curr->args_len)
		{
			if (ft_strchr(curr->args[i].value, '{')
				&& check_braces(curr->args[i].value))
				return (1);
			i++;
		}
	}
	return (0);
}
