/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouchta <obouchta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 07:19:14 by obouchta          #+#    #+#             */
/*   Updated: 2024/03/06 07:19:20 by obouchta         ###   ########.fr       */
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

int	get_args_helper(char *input, int *i, int *j, char **args)
{
	int	l;

	l = *i;
	while (input[l] && input[l] != ' ')
		l++;
	args[*j] = malloc(l - (*i) + 1);
	if (!args[*j])
		return (0);
	l = 0;
	while (input[*i] && input[*i] != ' ')
		args[*j][l++] = input[(*i)++];
	args[(*j)++][l] = '\0';
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
	args = malloc((calc_args_len(input, *i) + 2) * sizeof(char *));
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
		if (!get_args_helper(input, i, &j, args))
			return (NULL);
	}
	args[j] = NULL;
	return (args);
}

t_token	*get_cmd(char *input, int *i, int prev_type)
{
	int		j;
	char	*cmd;
	t_token	*new_token;

	j = *i;
	while (input[j] && input[j] != ' ')
		j++;
	cmd = malloc(j - *i + 1);
	if (!cmd)
		return (NULL);
	j = 0;
	while (input[*i] && input[*i] != ' ')
		cmd[j++] = input[(*i)++];
	cmd[j] = '\0';
	new_token = ft_lstnew(cmd, regonize_type_2(prev_type), get_args(input, i));
	if (!new_token)
		return (NULL);
	(*i)--;
	return (new_token);
}
