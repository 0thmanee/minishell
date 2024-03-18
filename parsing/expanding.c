/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouchta <obouchta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 02:58:32 by yboutsli          #+#    #+#             */
/*   Updated: 2024/03/18 03:19:52 by obouchta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
char *remove_char(char *str, int char_index)
{
	char	*tmp1;
	char	*tmp2;

	tmp1 = ft_substr(str, 0, char_index);
	tmp2 = ft_substr(str, char_index + 1, ft_strlen(str) - char_index - 1);
	free(str);
	if (!tmp1)
		return (tmp2);
	else if (!tmp2)
		return (tmp1);
	str = ft_strjoin(tmp1, tmp2);
	free(tmp1);
	free(tmp2);
	return (str);
}
char	*replace_mini_str(char *str, int start, int end, char *mini_str)
{
	char	*tmp1;
	char	*tmp2;
	char	*tmp3;

	tmp1 = ft_substr(str, 0, start);
	if (!tmp1 && mini_str)
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
char	*case_1(char *result, int *i, t_list *list_env)
{
	int		j;
	char	*tmp;
	char	*var;
	char	*value;

	j = 1;
	while (!char_is_valid(result[j + *i]))
		j++;
	var = ft_substr(result, *i + 1, j - 1);
	value = get_env(&list_env, var);
	free(var);
	var = NULL;
	if (value != NULL)
	{
		tmp = result;
		result = replace_mini_str(tmp, *i,  *i + j, value);
		*i += ft_strlen(value);
		free(tmp);
	}
	else
	{
		j = 1;
		while (!char_is_valid(result[j + *i]))
			j++;
		if (result[j + *i] != '\0')
			var = ft_substr(result, j + *i, ft_strlen(result) - j - *i);
		tmp = result;
		result = ft_substr(tmp, 0, *i - 1);
		free(tmp);
		if (var)
		{
			tmp = result;
			result = ft_strjoin(tmp, var);
			free(tmp);
			free(var);
			(*i)--;
		}
	}
	return (result);
}
char	*case_2(char *result, int *i)
{
	result = remove_char(result, *i);
	return (result);
}

char	*case_3(char *result, int *i)
{
	result = remove_char(result, *i);
	result = remove_char(result, *i);
	(*i)++;
	return (result);
}

char	*expanding_helper(t_list *list_env, char *value, int vars_len, int *vars)
{
	int	i;
	int	count;
	char *result;
	i = 0;
	count = 0;
	
	result = ft_strdup(value);
	if (!result)
		return (0);
	free(value);
	while (result[i] && count < vars_len)
	{
		if (result[i] == '$' && !result[i + 1])
			return (result);
		if (result[i] == '$' && result[i + 1] != '\0')
		{
			if (vars[count] == 0)
			{
				i++;
				count++;
				continue;
			}
			else if (vars[count] == 1)
				result = case_1(result, &i, list_env);
			else if (vars[count] == 2)
				result = case_2(result, &i);
			else if (vars[count] == 3)
				result = case_3(result, &i);
			if (!result)
				return (0);
			count++;
		}
		if (i > ft_strlen(result) || !result[i])
			break;
		else if (result[i] == '$')
			continue;
		
		i++;
	}
	return (result);
}

void	expanding(t_token **tokens, t_list *list_env)
{
	int	i;
	t_token	*curr;

	curr = *tokens;
	while (curr)
	{
		curr->value = expanding_helper(list_env,
			curr->value, curr->vars_len, curr->vars);
		i = -1;
		while (++i < curr->args_len)
			curr->args[i].value = expanding_helper(list_env, curr->args[i].value,
				curr->args[i].vars_len, curr->args[i].vars);
		curr = curr->next;
	}
}
