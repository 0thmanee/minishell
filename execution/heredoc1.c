/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouchta <obouchta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 22:26:57 by yboutsli          #+#    #+#             */
/*   Updated: 2024/04/19 19:35:00 by obouchta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*parse_helper(char *result, int *i, t_list *list_env, t_free **ptrs)
{
	int	arr[2];

	arr[0] = *i;
	arr[1] = calc_var_size(result, *i);
	if (result[*i + 1] == '{')
		result = case_4(result, arr, list_env, ptrs);
	else if (!ft_isdigit(result[*i + 1]))
		result = case_3(result, i, ptrs);
	else
		result = case_1(result, arr, list_env, ptrs);
	return (result);
}

static int	parse_heredoc1(char *result, int *i)
{
	int	status;

	status = 0;
	if (result[*i + 1] == '\"' || result[*i + 1] == '\''
		|| (ft_isalpha(result[*i + 1]) && result[*i + 1] != '_'
			&& result[*i + 1] != '?' && result[*i + 1] != '{'
			&& ft_isdigit(result[*i + 1])))
		status = 1;
	if (status)
	{
		(*i)++;
		return (1);
	}
	return (0);
}

char	*parse_heredoc(char *input, t_list *list_env, t_free **ptrs)
{
	int		i;
	char	*result;

	i = 0;
	result = ft_strdup(input, ptrs);
	while (result[i])
	{
		if (result[i] == '$' && !result[i + 1])
			return (result);
		if (result[i] == '$')
		{
			if (parse_heredoc1(result, &i))
				continue ;
			else
				result = parse_helper(result, &i, list_env, ptrs);
			if (!result)
				return (NULL);
		}
		if (i >= ft_strlen(result))
			break ;
		else if (result[i] == '$')
			continue ;
		i++;
	}
	return (result);
}
