/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding_cases_1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouchta <obouchta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 03:38:21 by obouchta          #+#    #+#             */
/*   Updated: 2024/04/25 16:08:32 by obouchta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_empty_var(char **value, int vars, t_free **ptrs)
{
	char	*tmp;

	if (*value && !(*value)[0] && vars)
	{
		tmp = *value;
		*value = NULL;
		ft_free_ptr(ptrs, tmp);
	}
}

void	case_1_helper(char **result, int *arr, t_free **ptrs)
{
	char	*var;
	char	*tmp;
	int		j;

	j = arr[1];
	var = NULL;
	tmp = NULL;
	if ((*result)[j + arr[0]] != '\0')
		var = ft_substr(*result, j + arr[0],
				ft_strlen(*result) - j - arr[0], ptrs);
	tmp = *result;
	*result = ft_substr(tmp, 0, arr[0], ptrs);
	ft_free_ptr(ptrs, tmp);
	if (var)
	{
		tmp = *result;
		*result = ft_strjoin(tmp, var, ptrs);
		ft_free_ptr(ptrs, tmp);
		ft_free_ptr(ptrs, var);
	}
}

void	make_tab(int tab[2], int i, int j)
{
	tab[0] = i;
	tab[1] = j;
}

void	utils1(int *i, int len, char *str[3], t_free **ptrs)
{
	*i += len;
	ft_free_ptr(ptrs, str[0]);
}

char	*case_1(char *result, int *arr, t_list *list_env, t_free **ptrs)
{
	int		j;
	char	*str[3];
	int		is_exit;
	int		tab[2];

	is_exit = 0;
	if (result[arr[0] + 1] == '?')
		is_exit = 1;
	j = arr[1];
	str[1] = ft_substr(result, arr[0] + 1, j - 1, ptrs);
	str[2] = get_env(&list_env, str[1], is_exit, ptrs);
	ft_free_ptr(ptrs, str[1]);
	if (str[2] != NULL)
	{
		str[0] = result;
		make_tab(tab, arr[0], arr[0] + j);
		result = replace_str(str[0], tab, str[2], ptrs);
		utils1(arr, ft_strlen(str[2]), str, ptrs);
	}
	else if (!is_exit)
		case_1_helper(&result, arr, ptrs);
	return (result);
}
