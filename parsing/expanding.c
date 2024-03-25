/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboutsli <yboutsli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 02:58:32 by yboutsli          #+#    #+#             */
/*   Updated: 2024/03/25 03:12:31 by yboutsli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *remove_char(char *str, int char_index, t_free **ptrs)
{
	char	*tmp1;
	char	*tmp2;

	tmp1 = ft_substr(str, 0, char_index, ptrs);
	tmp2 = ft_substr(str, char_index + 1, ft_strlen(str) - char_index - 1, ptrs);
	ft_free_ptr(ptrs, str);
	if (!tmp1)
		return (tmp2);
	else if (!tmp2)
		return (tmp1);
	str = ft_strjoin_2(tmp1, tmp2);
	ft_free_ptr(ptrs, tmp1);
	ft_free_ptr(ptrs, tmp2);
	return (str);
}

char	*replace_mini_str(char *str, int start, int end, char *mini_str, t_free **ptrs)
{
	char	*tmp1;
	char	*tmp2;
	char	*tmp3;

	tmp1 = ft_substr(str, 0, start, ptrs);
	if (!tmp1 && mini_str)
		tmp2 = ft_strdup(mini_str, ptrs);
	else
	{
		tmp2 = ft_strjoin_2(tmp1, mini_str);
		ft_free_ptr(ptrs, tmp1);
	}
	tmp3 = ft_substr(str, end, ft_strlen(str) - end + 1, ptrs);
	if (!tmp3)
		return (tmp2);
	else
		tmp1 = ft_strjoin_2(tmp2, tmp3);
	ft_free_ptr(ptrs, tmp3);
	ft_free_ptr(ptrs, tmp2);
	return (tmp1);
}

int char_is_valid(char c)
{
	if (!(c >= 'a' && c <= 'z')
		&& !(c >= 'A' && c <= 'Z')
		&& !(c >= '0' && c <= '9') && c != '_')
		return (1);
	else
		return (0);
}
char	*case_1(char *result, int *i, t_list *list_env, t_free **ptrs)
{
	int		j;
	char	*tmp;
	char	*var;
	char	*value;

	j = 1;
	while (!char_is_valid(result[j + *i]))
		j++;
	var = ft_substr(result, *i + 1, j - 1, ptrs);
	value = get_env(&list_env, var);
	ft_free_ptr(ptrs, var);
	var = NULL;
	if (value != NULL)
	{
		tmp = result;
		result = replace_mini_str(tmp, *i,  *i + j, value, ptrs);
		*i += ft_strlen(value);
		ft_free_ptr(ptrs, tmp);
	}
	else
	{
		j = 1;
		while (!char_is_valid(result[j + *i]))
			j++;
		if (result[j + *i] != '\0')
			var = ft_substr(result, j + *i, ft_strlen(result) - j - *i, ptrs);
		tmp = result;
		result = ft_substr(tmp, 0, *i - 1, ptrs);
		ft_free_ptr(ptrs, tmp);
		if (var)
		{
			tmp = result;
			result = ft_strjoin_2(tmp, var);
			ft_free_ptr(ptrs, tmp);
			ft_free_ptr(ptrs, var);
			(*i)--;
		}
	}
	return (result);
}

char	*case_2(char *result, int *i, t_free **ptrs)
{
	result = remove_char(result, *i, ptrs);
	return (result);
}


char	*case_3(char *result, int *i, t_free **ptrs)
{
	result = remove_char(result, *i, ptrs);
	result = remove_char(result, *i, ptrs);
	(*i)++;
	return (result);
}

char	*expanding_helper1(t_list *list_env, t_token *token, t_free **ptrs)
{
	int	i;
	int	count;
	char *result;

	(i = 0, count = 0, result = ft_strdup(token->value, ptrs));
	while (result[i] && count < token->vars_len)
	{
		if (result[i] == '$' && !result[i + 1])
			return (result);
		if (result[i] == '$' && result[i + 1] != '\0')
		{
			if (token->vars[count] == 0)
			{
				i++;
				count++;
				continue;
			}
			else if (token->vars[count] == 1)
				result = case_1(result, &i, list_env, ptrs);
			else if (token->vars[count] == 2)
				result = case_2(result, &i, ptrs);
			else if (token->vars[count] == 3)
				result = case_3(result, &i, ptrs);
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

char	*expanding_helper2(t_list *list_env, t_value args, t_free **ptrs)

{
	int	i;
	int	count;
	char *result;

	(i = 0, count = 0, result = ft_strdup(args.value, ptrs));
	while (result[i] && count < args.vars_len)
	{
		if (result[i] == '$' && !result[i + 1])
			return (result);
		if (result[i] == '$' && result[i + 1] != '\0')
		{
			if (args.vars[count] == 0)
			{
				i++;
				count++;
				continue;
			}
			else if (args.vars[count] == 1)
				result = case_1(result, &i, list_env, ptrs);
			else if (args.vars[count] == 2)
				result = case_2(result, &i, ptrs);
			else if (args.vars[count] == 3)
				result = case_3(result, &i, ptrs);
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

void	expanding(t_token **tokens, t_list *list_env, t_free **ptrs)
{
	int	i;
	t_token	*curr;
	char	*tmp_val;

	curr = *tokens;
	while (curr)
	{
		tmp_val = curr->value;
		curr->value = expanding_helper1(list_env, curr, ptrs);
		ft_free_ptr(ptrs, tmp_val);
		i = -1;
		while (++i < curr->args_len)
		{
			tmp_val = curr->args[i].value;
			curr->args[i].value = expanding_helper2(list_env, curr->args[i], ptrs);
			ft_free_ptr(ptrs, tmp_val);
		}
		curr = curr->next;
	}
}
