/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trim_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboutsli <yboutsli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 09:02:08 by obouchta          #+#    #+#             */
/*   Updated: 2024/04/19 21:05:51 by yboutsli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	trim_input(char **input, t_free **ptrs)
{
	int		i;
	int		start;
	int		new_len;
	char	*tmp;

	i = 0;
	new_len = 0;
	tmp = *input;
	while ((*input)[i] && is_whitespace((*input)[i]))
		i++;
	if (i == ft_strlen(*input))
	{
		*input = NULL;
		ft_free_ptr(ptrs, tmp);
		return ;
	}
	start = i--;
	while ((*input)[++i])
		new_len++;
	while (--i >= 0 && is_whitespace((*input)[i]))
		new_len--;
	*input = ft_substr(*input, start, new_len, ptrs);
	ft_free_ptr(ptrs, tmp);
}
