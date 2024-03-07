/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd copy.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouchta <obouchta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 07:19:14 by obouchta          #+#    #+#             */
/*   Updated: 2024/03/07 06:19:31 by obouchta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int calc_args_len_helper(char *input, int *i, int *len)
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
		while (input[*i] && input[*i] != ' ')
			(*i)++;
		(*len)++;
	}
	return (pass);
}

int calc_args_len(char *input, int i)
{
	int len = 0;
	int l = 0;

	while (input[i])
	{
		while (input[i] && input[i] == ' ')
			i++;
		if (calc_args_len_helper(input, &i, &len))
			continue ;
		if (regonize_type(input, i))
			break;
		while (input[i] && input[i] != ' ')
		{
			i++;
			l++;
		}
		if (l)
			len++;
		l = 0;
	}
	return (len);
}

int	calc_cmd_len(char *input, int *i)
{
	int		j;
	char	quote;

	j = *i;
	while (input[j] && input[j] != ' ')
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

int	extract_expr(char *src, char *dest, int *i)
{
	char	quote;
	int		j;

	j = 0;
	dest = malloc(calc_cmd_len(src, i) - *i + 1);
	if (!dest)
		return (0);
	while (src[*i] && src[*i] != ' ')
	{
		if (src[*i] == '\'' || src[*i] == '\"')
		{
			quote = src[*i];
			dest[j++] = src[(*i)++];
			while (src[*i] && src[*i] != quote)
				dest[j++] = src[(*i)++];
		}
		dest[j++] = src[(*i)++];
	}
	dest[j] = '\0';
	return (1);
}

char **get_args(char *input, int *i)
{
	int j;
	int len;
	char **args;

	j = 0;
	len = calc_args_len(input, *i);
	if (!len)
		return (NULL);
	args = malloc((len + 2) * sizeof(char *));
	if (!args)
		return (NULL);
	while (input[*i])
	{
		while (input[*i] && input[*i] == ' ')
			(*i)++;
		if (input[*i] == '\'' || input[*i] == '\"')
		{
			args[j++] = quoted_cmd(input, i);
			continue ;
		}
		if (regonize_type(input, *i) != EXPRESSION)
			break;
		if (!extract_expr(input, args[j], i))
			return (NULL);
		j++;
	}
	args[j] = NULL;
	return (args);
}

t_token	*get_cmd(char *input, int *i, int prev_type)
{
	char	*cmd;
	t_token	*new_token;

	cmd = NULL;
	extract_expr(input, cmd, i);
	new_token = ft_lstnew(cmd, regonize_type_2(prev_type), get_args(input, i));
	if (!new_token)
		return (NULL);
	(*i)--;
	return (new_token);
}
