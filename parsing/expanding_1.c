/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouchta <obouchta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 02:58:32 by yboutsli          #+#    #+#             */
/*   Updated: 2024/04/06 05:00:24 by obouchta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*utils4(int type, char *result, int *i, t_new_1 new)
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

int	utils_5(char **result, int *i, int *count, t_new_1 new_strct)
{
	if ((*result)[*i] == '$' && (*result)[*i + 1] != '\0')
	{
		if (new_strct.token->vars[*count] == 0)
		{
			utils2(i, count);
			return (1);
		}
		else
			*result = utils4(new_strct.token->vars[*count],
					(*result), i, new_strct);
		if (!(*result))
			return (2);
		(*count)++;
	}
	return (0);
}

t_new_1	create_new_1(t_list **list_env, t_free **ptrs, t_token *token)
{
	t_new_1	new_strct;

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
	t_new_1	new_strct;
	int		utils_5_res;

	result = exp_init(&i, &count, ft_strdup(token->value, ptrs));
	new_strct = create_new_1(&list_env, ptrs, token);
	while (result[i] && count < token->vars_len)
	{
		if (result[i] == '$' && !result[i + 1])
			return (result);
		utils_5_res = utils_5(&result, &i, &count, new_strct);
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
