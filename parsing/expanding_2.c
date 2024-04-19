/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouchta <obouchta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 04:36:31 by obouchta          #+#    #+#             */
/*   Updated: 2024/04/19 17:20:28 by obouchta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_new_2	create_new_2(t_list **list_env, t_free **ptrs, t_value args)
{
	t_new_2	new_strct;

	new_strct.env = *list_env;
	new_strct.ptrs = ptrs;
	new_strct.args = args;
	return (new_strct);
}

char	*utils4_1(t_var var, char *result, int *i, t_new_2 new_strct)
{
	int	arr[2];

	arr[0] = *i;
	arr[1] = var.size;
	if (var.mode == 1)
		result = case_1(result, arr, new_strct.env, new_strct.ptrs);
	else if (var.mode == 2)
		result = case_2(result, arr, new_strct.ptrs);
	else if (var.mode == 3)
		result = case_3(result, arr, new_strct.ptrs);
	else if (var.mode == 4)
		result = case_4(result, arr, new_strct.env, new_strct.ptrs);
	*i = arr[0];
	return (result);
}

int	utils_5_1(char **result, int *i, int *count, t_new_2 new_strct)
{
	if ((*result)[*i] == '$' && (*result)[*i + 1] != '\0')
	{
		if (new_strct.args.vars[*count].mode == 0)
		{
			utils2(i, count);
			return (1);
		}
		else
			*result = utils4_1(new_strct.args.vars[*count],
					(*result), i, new_strct);
		if (!(*result))
			return (2);
		(*count)++;
	}
	return (0);
}

char	*expanding_2(t_list *list_env, t_value args, t_free **ptrs)

{
	int		i;
	int		count;
	char	*result;
	t_new_2	new_strct;
	int		utils_5_res;

	result = exp_init(&i, &count, ft_strdup(args.value, ptrs));
	new_strct = create_new_2(&list_env, ptrs, args);
	while (result[i] && count < args.vars_len)
	{
		if (result[i] == '$' && !result[i + 1])
			return (result);
		utils_5_res = utils_5_1(&result, &i, &count, new_strct);
		if (utils_5_res == 1)
			continue ;
		else if (utils_5_res == 2)
			return (0);
		if (i > ft_strlen(result) || !result[i])
			break ;
		else if (result[i] == '$')
			continue ;
		i++;
	}
	return (result);
}
