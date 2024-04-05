/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouchta <obouchta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 02:58:32 by yboutsli          #+#    #+#             */
/*   Updated: 2024/04/05 02:09:02 by obouchta         ###   ########.fr       */
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
	str = ft_strjoin(tmp1, tmp2, ptrs);
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
		tmp2 = ft_strjoin(tmp1, mini_str, ptrs);
		ft_free_ptr(ptrs, tmp1);
	}
	tmp3 = ft_substr(str, end, ft_strlen(str) - end + 1, ptrs);
	if (!tmp3)
		return (tmp2);
	else
		tmp1 = ft_strjoin(tmp2, tmp3, ptrs);
	ft_free_ptr(ptrs, tmp3);
	ft_free_ptr(ptrs, tmp2);
	return (tmp1);
}

void	case_1_helper(char **result, int *i, t_free **ptrs)
{
	char	*var;
	char	*tmp;
	int		j;

	(j = 1, var = NULL, tmp = NULL);
	while (!char_is_valid((*result)[j + *i]))
		j++;
	if ((*result)[j + *i] != '\0')
		var = ft_substr(*result, j + *i, ft_strlen(*result) - j - *i, ptrs);
	tmp = *result;
	*result = ft_substr(tmp, 0, *i, ptrs);
	ft_free_ptr(ptrs, tmp);
	if (var)
	{
		(tmp = *result, *result = ft_strjoin(tmp, var, ptrs));
		(ft_free_ptr(ptrs, tmp), ft_free_ptr(ptrs, var));
	}
}

char	*case_1(char *result, int *i, t_list *list_env, t_free **ptrs)
{
	int		j;
	char	*tmp;
	char	*var;
	char	*value;
	int		is_exit;

	(j = 1, is_exit = 0);
	if (result[j + *i] == '?')
		(is_exit = 1, j++);
	else
		while (!char_is_valid(result[j + *i]))
			j++;
	var = ft_substr(result, *i + 1, j - 1, ptrs);
	value = get_env(&list_env, var);
	(ft_free_ptr(ptrs, var), var = NULL);
	if (value != NULL)
	{
		tmp = result;
		result = replace_mini_str(tmp, *i,  *i + j, value, ptrs);
		(*i += ft_strlen(value), ft_free_ptr(ptrs, tmp));
	}
	else if (!is_exit)
		case_1_helper(&result, i, ptrs);
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

void	case_4_helper(char **result, int *i, t_free **ptrs)
{
	char	*var;
	char	*tmp;
	int		j;

	(j = 2, var = NULL, tmp = NULL);
	while ((*result)[j + *i] && (*result)[j + *i] != '}')
		j++;
	if ((*result)[j + *i] == '}')
		j++;
	if ((*result)[j + *i] != '\0')
		var = ft_substr(*result, j + *i, ft_strlen(*result) - j - *i, ptrs);
	tmp = *result;
	*result = ft_substr(tmp, 0, *i, ptrs);
	ft_free_ptr(ptrs, tmp);
	if (var)
	{
		(tmp = *result, *result = ft_strjoin(tmp, var, ptrs));
		(ft_free_ptr(ptrs, tmp), ft_free_ptr(ptrs, var));
	}
}

char	*case_4(char *result, int *i, t_list *list_env, t_free **ptrs)
{
	int		j;
	char	*tmp;
	char	*var;
	char	*value;

	j = 2;
	while (result[j + *i] && result[j + *i] != '}')
		j++;
	var = ft_substr(result, *i + 2, j - 2, ptrs);
	value = get_env(&list_env, var);
	(ft_free_ptr(ptrs, var), var = NULL);
	if (value != NULL)
	{
		tmp = result;
		result = replace_mini_str(tmp, *i,  *i + j + 1, value, ptrs);
		(*i += ft_strlen(value) + 1, ft_free_ptr(ptrs, tmp));
	}
	else
		case_4_helper(&result, i, ptrs);
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
			else if (token->vars[count] == 4)
				result = case_4(result, &i, list_env, ptrs);
			if (!result)
				return (0);
			count++;
		}
		if (i >= ft_strlen(result))
			break ;
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
			else if (args.vars[count] == 4)
				result = case_4(result, &i, list_env, ptrs);
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
		if (curr->type == DELIMITER)
		{
			curr = curr->next;
			continue ;
		}
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
