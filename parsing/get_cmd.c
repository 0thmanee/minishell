/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouchta <obouchta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 07:19:14 by obouchta          #+#    #+#             */
/*   Updated: 2024/03/20 03:06:24 by obouchta         ###   ########.fr       */
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
		while (input[*i] && !is_whitespace(input[*i]))
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
		while (input[i] && is_whitespace(input[i]))
			i++;
		if (calc_args_len_helper(input, &i, &len))
			continue ;
		if (regonize_type(input, i))
			break;
		while (input[i] && !is_whitespace(input[i]))
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

int	extract_expr(char *src, char **dest, int *i)
{
	char	quote;
	int		j;

	j = 0;
	(*dest) = malloc(calc_cmd_len(src, i) - *i + 1);
	if (!(*dest))
		return (0);
	while (src[*i] && !is_whitespace(src[*i]))
	{
		if (src[*i] == '\'' || src[*i] == '\"')
		{
			quote = src[*i];
			(*dest)[j++] = src[(*i)++];
			while (src[*i] && src[*i] != quote)
				(*dest)[j++] = src[(*i)++];
		}
		(*dest)[j++] = src[(*i)++];
	}
	(*dest)[j++] = '\0';
	return (1);
}

int	extract_expr_2(char *src, t_value *dest, int *i, int *j)
{
	char	quote;
	int		k;

	k = 0;
	dest[*j].value = malloc(calc_cmd_len(src, i) - *i + 1);
	if (!dest[*j].value)
		return (0);
	while (src[*i] && !is_whitespace(src[*i]))
	{
		if (src[*i] == '\'' || src[*i] == '\"')
		{
			quote = src[*i];
			dest[*j].value[k++] = src[(*i)++];
			while (src[*i] && src[*i] != quote)
				dest[*j].value[k++] = src[(*i)++];
		}
		dest[*j].value[k++] = src[(*i)++];
	}
	dest[*j].value[k++] = '\0';
	return (1);
}

int	get_quoted_arg(char *input, int *i, int *j, t_value *args)
{
	while (input[*i] && is_whitespace(input[*i]))
		(*i)++;
	if (input[*i] == '\'' || input[*i] == '\"')
	{
		args[*j].value = quoted_cmd(input, i);
		(*j)++;
		return (1);
	}
	return (0);
}

t_value *get_values(char *input, int *i, int *args_len)
{
	int j;
	t_value *args;
	int		quoted_status;

	j = 0;
	*args_len = calc_args_len(input, *i);
	if (!*args_len)
		return (NULL);
	args = malloc((*args_len + 1) * sizeof(t_value));
	if (!args)
		return (NULL);
	while (input[*i])
	{
		quoted_status = get_quoted_arg(input, i, &j, args);
		if (quoted_status == 1)
			continue ;
		else if (quoted_status == -1)
			return (NULL);
		if (regonize_type(input, *i) != EXPRESSION)
			break;
		if (!extract_expr_2(input, args, i, &j))
			return (NULL);
		j++;
	}
	j = 0;
	return (args);
}

t_token	*get_cmd(char *input, int *i, int prev_type)
{
	char	*cmd;
	t_token	*new_token;
	int		args_len;

	cmd = NULL;
	if (!extract_expr(input, &cmd, i))
		return (NULL);
	new_token = ft_lstnew_1(cmd, regonize_type_2(prev_type),
		get_values(input, i, &args_len));
	if (!new_token)
		return (NULL);
	new_token->args_len = args_len;
	if (input[*i])
		(*i)--;
	return (new_token);
}
