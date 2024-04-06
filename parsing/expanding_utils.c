/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouchta <obouchta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 03:40:19 by obouchta          #+#    #+#             */
/*   Updated: 2024/04/06 05:03:14 by obouchta         ###   ########.fr       */
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
