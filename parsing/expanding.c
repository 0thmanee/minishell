/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboutsli <yboutsli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 02:58:32 by yboutsli          #+#    #+#             */
/*   Updated: 2024/04/06 03:33:08 by yboutsli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*remove_char(char *str, int char_index, t_free **ptrs)
{
	char	*tmp1;
	char	*tmp2;

	tmp1 = ft_substr(str, 0, char_index, ptrs);
	tmp2 = ft_substr(str, char_index + 1,
			ft_strlen(str) - char_index - 1, ptrs);
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

char	*replace_str(char *str, int tab[2], char *min_str, t_free **ptrs)
{
	char	*tmp1;
	char	*tmp2;
	char	*tmp3;

	tmp1 = ft_substr(str, 0, tab[0], ptrs);
	if (!tmp1 && min_str)
		tmp2 = ft_strdup(min_str, ptrs);
	else
	{
		tmp2 = ft_strjoin(tmp1, min_str, ptrs);
		ft_free_ptr(ptrs, tmp1);
	}
	tmp3 = ft_substr(str, tab[1], ft_strlen(str) - tab[1] + 1, ptrs);
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

	j = 1;
	var = NULL;
	tmp = NULL;
	while (!char_is_valid((*result)[j + *i]))
		j++;
	if ((*result)[j + *i] != '\0')
		var = ft_substr(*result, j + *i, ft_strlen(*result) - j - *i, ptrs);
	tmp = *result;
	*result = ft_substr(tmp, 0, *i, ptrs);
	ft_free_ptr(ptrs, tmp);
	if (var)
	{
		tmp = *result;
		*result = ft_strjoin(tmp, var, ptrs);
		ft_free_ptr(ptrs, tmp);
		ft_free_ptr(ptrs, var);
	}
}

void	exit_case(int *is_exit, int *j)
{
	*is_exit = 1;
	(*j)++;
}

void	make_tab(int tab[2], int i, int j)
{
	tab[0] = i;
	tab[1] = j;
}

void	utils1(int *i, char *str[3], t_free **ptrs)
{
	*i += ft_strlen(str[2]);
	ft_free_ptr(ptrs, str[0]);
}

char	*case_1(char *result, int *i, t_list *list_env, t_free **ptrs)
{
	int		j;
	char	*str[3];
	int		is_exit;
	int		tab[2];

	j = 1;
	is_exit = 0;
	if (result[j + *i] == '?')
		exit_case(&is_exit, &j);
	else
		while (!char_is_valid(result[j + *i]))
			j++;
	str[1] = ft_substr(result, *i + 1, j - 1, ptrs);
	str[2] = get_env(&list_env, str[1]);
	ft_free_ptr(ptrs, str[1]);
	if (str[2] != NULL)
	{
		str[0] = result;
		make_tab(tab, *i, *i + j);
		result = replace_str(str[0], tab, str[2], ptrs);
		utils1(i, str, ptrs);
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

void	case4_init(int *j, char *str[2])
{
	*j = 2;
	str[0] = NULL;
	str[1] = NULL;
}

void	case_4_helper(char **result, int *i, t_free **ptrs)
{
	char	*str[3];
	int		j;

	case4_init(&j, str);
	while ((*result)[j + *i] && (*result)[j + *i] != '}')
		j++;
	if ((*result)[j + *i] == '}')
		j++;
	if ((*result)[j + *i] != '\0')
		str[0] = ft_substr(*result, j + *i, ft_strlen(*result) - j - *i, ptrs);
	str[1] = *result;
	*result = ft_substr(str[1], 0, *i, ptrs);
	ft_free_ptr(ptrs, str[1]);
	if (str[0])
	{
		str[1] = *result;
		*result = ft_strjoin(str[1], str[0], ptrs);
		ft_free_ptr(ptrs, str[1]);
		ft_free_ptr(ptrs, str[0]);
	}
}

char	*case_4(char *result, int *i, t_list *list_env, t_free **ptrs)
{
	int		j;
	char	*tmp;
	char	*var;
	char	*value;
	int		tab[2];

	j = 2;
	while (result[j + *i] && result[j + *i] != '}')
		j++;
	var = ft_substr(result, *i + 2, j - 2, ptrs);
	value = get_env(&list_env, var);
	(ft_free_ptr(ptrs, var), var = NULL);
	if (value != NULL)
	{
		tmp = result;
		tab[0] = *i;
		tab[1] = *i + j + 1;
		result = replace_str(tmp, tab, value, ptrs);
		*i += ft_strlen(value) + 1;
		ft_free_ptr(ptrs, tmp);
	}
	else
		case_4_helper(&result, i, ptrs);
	return (result);
}

char	*exp_init(int *i, int *count, char *new_result)
{
	*i = 0;
	*count = 0;
	return (new_result);
}
void	utils2(int *i, int *count)
{
	(*i)++;
	(*count)++;
}

char	*utils4(int type, char *result, int *i, t_new new)
{
	if (type == 1)
		result = case_1(result, i, new.env, new.ptrs);
	else if (type == 2)
		result = case_2(result, i, new.ptrs);
	else if (type == 3)
		result = case_3(result, i, new.ptrs);
	else if (type == 4)
		result = case_4(result, i, new.env, new.ptrs);
	return (result);
}

int	utils_5(char **result, int *i, int *count, t_new new)
{
	if ((*result)[*i] == '$' && (*result)[*i + 1] != '\0')
	{
		if (new.token->vars[*count] == 0)
		{
			utils2(i, count);
			return (1);
		}
		else
			*result = utils4(new.token->vars[*count], (*result), i, new);
		if (!(*result))
			return (2);
		(*count)++;
	}
	return (0);
}

t_new create_new(t_list **list_env, t_free **ptrs, t_token *token)
{
	t_new	new_strct;
	new_strct.env = *list_env;
	new_strct.ptrs = ptrs;
	new_strct.token = token;
	return (new_strct);
}

char	*expanding_1(t_list *list_env, t_token *token, t_free **ptrs)
{
	int		i;
	int		count;
	char	*result;
	t_new	new;
	int		utils_5_res;

	result = exp_init(&i, &count, ft_strdup(token->value, ptrs));
	new = create_new(&list_env, ptrs, token);
	while (result[i] && count < token->vars_len)
	{
		if (result[i] == '$' && !result[i + 1])
			return (result);
		utils_5_res = utils_5(&result, &i, &count, new);
		if (utils_5_res == 1)
			continue ;
		else if (utils_5_res == 2)
			return (0);
		if (i >= ft_strlen(result))
			break ;
		else if (result[i] == '$')
			continue ;
		i++;
	}
	return (result);
}

char	*expanding_2(t_list *list_env, t_value args, t_free **ptrs)

{
	int		i;
	int		count;
	char	*result;

	result = exp_init(&i, &count, ft_strdup(args.value, ptrs));
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
				continue ;
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
			break ;
		else if (result[i] == '$')
			continue ;
		i++;
	}
	return (result);
}

void	expanding(t_token **tokens, t_list *list_env, t_free **ptrs)
{
	int		i;
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
		curr->value = expanding_1(list_env, curr, ptrs);
		ft_free_ptr(ptrs, tmp_val);
		i = -1;
		while (++i < curr->args_len)
		{
			tmp_val = curr->args[i].value;
			curr->args[i].value = expanding_2(list_env, curr->args[i], ptrs);
			ft_free_ptr(ptrs, tmp_val);
		}
		curr = curr->next;
	}
}
