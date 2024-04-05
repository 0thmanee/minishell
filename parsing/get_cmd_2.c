/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouchta <obouchta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 03:49:50 by obouchta          #+#    #+#             */
/*   Updated: 2024/04/05 03:53:47 by obouchta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	calc_args_len_helper1(char *input, int *i, int *len)
{
	char	quote;
	int		pass;

	pass = 0;
	if (input[*i] == '\'' || input[*i] == '\"')
	{
		pass = 1;
		quote = input[*i];
		(*i)++;
		while (input[*i] && input[*i] != quote)
			(*i)++;
		if (input[*i])
			(*i)++;
		while (input[*i] && !is_whitespace(input[*i]))
			(*i)++;
		(*len)++;
	}
	return (pass);
}

void	calc_args_len_helper2(char *input, int *i, int *len)
{
	char	quote;
	int		l;

	l = 0;
	while (input[*i] && !is_whitespace(input[*i]))
	{
		if (input[*i] == '\'' || input[*i] == '\"')
		{
			quote = input[(*i)++];
			while (input[*i] != quote)
				(*i)++;
		}
		(*i)++;
		l++;
	}
	if (l)
		(*len)++;
}

int	calc_args_len(char *input, int i)
{
	int	len;

	len = 0;
	while (input[i])
	{
		while (input[i] && is_whitespace(input[i]))
			i++;
		if (regonize_type(input, i))
			break ;
		if (calc_args_len_helper1(input, &i, &len))
			continue ;
		calc_args_len_helper2(input, &i, &len);
	}
	return (len);
}

int	calc_cmd_len(char *input, int *i)
{
	int		j;
	char	quote;

	j = *i;
	while (input[j] && !is_whitespace(input[*i]))
	{
		if (input[j] == '\'' || input[j] == '\"')
		{
			quote = input[j];
			j++;
			while (input[j] && input[j] != quote)
				j++;
		}
		j++;
	}
	return (j);
}
