/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboutsli <yboutsli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 02:58:32 by yboutsli          #+#    #+#             */
/*   Updated: 2024/03/15 15:56:02 by yboutsli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*replace_mini_str(char *str, int start, int end, char *mini_str)
{
	char	*tmp1;
	char	*tmp2;
	char	*tmp3;

	tmp1 = ft_substr(str, 0, start);
	if (!tmp1)
		tmp2 = ft_strdup(mini_str);
	else
	{
		tmp2 = ft_strjoin(tmp1, mini_str);
		free(tmp1);
	}
	tmp3 = ft_substr(str, end, ft_strlen(str) - end + 1);
	if (!tmp3)
		return (tmp2);
	else
		tmp1 = ft_strjoin(tmp2, tmp3); 
	free(tmp3);
	free(tmp2);
	return (tmp1);
}
int char_is_valid(char c)
{
    if (c == '$' || c == '.' || c == '!' || c == '@' || c == '#' || c == '\0' || c == ' ' || c == '-')
		return (1);
	else
		return (0);
}
char	*expanding(char *str, t_list *list_env)
{
	int	i;
	int	j;
	char *var;
	char *value;
	char *result;

	result = ft_strdup(str);
	i = 0;
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1] != '\0')
		{
			j = 1;
			while (!char_is_valid(str[j + i]))
				j++;
			var = ft_substr(str, i + 1, j - 1);
			value = get_env(&list_env, var);
			free(var);
			if (value != NULL)
			{
				result = replace_mini_str(str, i,  i + j, value);
				free(str);
				return (expanding(result, list_env));
			}
		}
		i++;
	}
	return (result);
}