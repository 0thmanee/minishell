/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboutsli <yboutsli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 22:26:57 by yboutsli          #+#    #+#             */
/*   Updated: 2024/04/05 22:30:22 by yboutsli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*utils2(char *result, int *i, t_list *list_env, t_free **ptrs)
{
	if (result[*i + 1] == '{')
		result = case_4(result, i, list_env, ptrs);
	else if (!ft_isdigit(result[*i + 1]))
		result = case_3(result, i, ptrs);
	else
		result = case_1(result, i, list_env, ptrs);
	return (result);
}

static int	parse_heredoc1(char *result, int *i)
{
	int	status;

	status = 0;
	if (result[*i + 1] == '\"' || result[*i + 1] == '\''
		|| (ft_isalpha(result[*i + 1]) && result[*i + 1] != '_'
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
				result = utils2(result, &i, list_env, ptrs);
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
