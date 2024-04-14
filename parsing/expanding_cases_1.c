/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding_cases_1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouchta <obouchta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 03:38:21 by obouchta          #+#    #+#             */
/*   Updated: 2024/04/14 16:52:28 by obouchta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	utils1(int *i, int len, char *str[3], t_free **ptrs)
{
	*i += len;
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
	str[2] = get_env(&list_env, str[1], is_exit, ptrs);
	ft_free_ptr(ptrs, str[1]);
	if (str[2] != NULL)
	{
		str[0] = result;
		make_tab(tab, *i, *i + j);
		result = replace_str(str[0], tab, str[2], ptrs);
		utils1(i, ft_strlen(str[2]), str, ptrs);
	}
	else if (!is_exit)
		case_1_helper(&result, i, ptrs);
	return (result);
}
