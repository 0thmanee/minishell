/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding_cases_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouchta <obouchta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 03:41:44 by obouchta          #+#    #+#             */
/*   Updated: 2024/04/06 03:41:59 by obouchta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
