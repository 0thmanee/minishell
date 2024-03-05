/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_len.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouchta <obouchta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 10:58:53 by obouchta          #+#    #+#             */
/*   Updated: 2024/03/04 21:31:08 by obouchta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	valid_quotes(char *input)
{
	int		i;
	char	quote;

	i = 0;
	while (input[i])
	{
		if (input[i] == '\'' || input[i] == '\"')
		{
			quote = input[i];
			i++;
			while (input[i] && input[i] != quote)
				i++;
			if (!input[i])
				return (0);
			else
				i++;
		}
		else
			i++;
	}
	return (1);
}

void	ft_new_len_helper_1(char *input, int i, int *new_len)
{
	if (input[i] == '<' || input[i] == '>')
	{
		if ((input[i] == '<' && input[i + 1] == '<') ||
			(input[i] == '>' && input[i + 1] == '>'))
		{
			if (i > 0 && input[i - 1] != ' ')
				(*new_len)++;
			if (input[i + 2] && input[i + 2] != ' ')
				(*new_len)++;
			i++;
		}
		else
		{
			if (i > 0 && input[i - 1] != ' ')
				(*new_len)++;
			if (input[i + 1] && input[i + 1] != ' ')
				(*new_len)++;
		}
	}
}

void new_len_helper_2(char *input, int i, int *new_len)
{
	if (input[i] == '\'')
	{
		if (i > 0 && input[i - 1] != ' ')
			(*new_len)++;
		(*new_len)++;
		i++;
		while (input[i] && input[i] != '\'')
		{
			(*new_len)++;
			i++;
		}
		if (input[i])
			(*new_len)++;
		if (input[i] && input[i] != ' ')
			(*new_len)++;
	}
	else
	{
		if (i > 0 && input[i - 1] != ' ')
			(*new_len)++;
		(*new_len)++;
		i++;
		while (input[i] && input[i] != '\"')
		{
			(*new_len)++;
			i++;
		}
		if (input[i])
			(*new_len)++;
		if (input[i] && input[i] != ' ')
			(*new_len)++;
	}
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
		if (input[i] == '<' || input[i] == '>')
			ft_new_len_helper_1(input, i, &new_len);
		else if (input[i] == '\'' || input[i] == '\"')
			new_len_helper_2(input, i, &new_len);
		else if (input[i] == '|' || input[i] == '$')
		{
			if (i > 0 && input[i - 1] != ' ')
				new_len++;
			if (input[i] == '|' && input[i + 1] && input[i + 1] != ' ')
				new_len++;
		}
	}
	return (new_len);
}
