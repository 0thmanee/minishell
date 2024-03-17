/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_len.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouchta <obouchta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 10:58:53 by obouchta          #+#    #+#             */
/*   Updated: 2024/03/13 17:04:21 by obouchta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_new_len_helper(char *input, int i, int *new_len)
{
	if (input[i] == '<' || input[i] == '>')
	{
		if ((input[i] == '<' && input[i + 1] == '<') ||
			(input[i] == '>' && input[i + 1] == '>'))
		{
			if (i > 0 && !is_whitespace(input[i - 1]))
				(*new_len)++;
			if (input[i + 2] && input[i + 2] != ' ')
				(*new_len)++;
			i++;
		}
		else
		{
			if (i > 0 && !is_whitespace(input[i - 1]))
				(*new_len)++;
			if (input[i + 1] && !is_whitespace(input[i + 1]))
				(*new_len)++;
		}
	}
}

// void new_len_helper_2(char *input, int i, int *new_len)
// {
// 	char	quote;

// 	quote = input[i];
// 	if (i > 0 && !is_whitespace(input[i - 1]))
// 		(*new_len)++;
// 	(*new_len)++;
// 	i++;
// 	while (input[i] && input[i] != quote)
// 	{
// 		(*new_len)++;
// 		i++;
// 	}
// 	if (input[i])
// 		(*new_len)++;
// 	if (input[i] && !is_whitespace(input[i]))
// 		(*new_len)++;
// }

int	quoted(char *input, int i)
{
	int		j;
	int		k;
	char	quote;

	j = 0;
	while (input[j])
	{
		if (input[j] == '\'' || input[j] == '\"')
		{
			quote = input[j];
			k = j;
			j++;
			while (input[j] && input[j] != quote)
				j++;
			if (i >= k && i <= j)
				return (quote);
		}
		if (input[j])
			j++;
	}
	return (0);
}

int	ft_new_len(char *input)
{
	int	i;
	int	len;
	int	new_len;

	i = -1;
	len = ft_strlen(input);
	new_len = len;
	while (input[++i])
	{
		if ((input[i] == '<' || input[i] == '>') && !quoted(input, i))
		{
			ft_new_len_helper(input, i, &new_len);
		}
		else if ((input[i] == '|' || input[i] == '$') && !quoted(input, i))
		{
			if (i > 0 && !is_whitespace(input[i - 1]))
				new_len++;
			if (input[i] == '|' && input[i + 1]
				&& !is_whitespace(input[i + 1]))
				new_len++;
		}
	}
	return (new_len);
}
