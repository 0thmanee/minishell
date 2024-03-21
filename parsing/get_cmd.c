/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouchta <obouchta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 07:19:14 by obouchta          #+#    #+#             */
/*   Updated: 2024/03/21 05:28:37 by obouchta         ###   ########.fr       */
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

int	extract_expr(char *src, char **dest, int *i, t_free **ptrs)
{
	char	quote;
	int		j;

	j = 0;
	(*dest) = ft_malloc1(ptrs, calc_cmd_len(src, i) - *i + 1);
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

int	extract_expr_2(char *src, t_value *dest, int *i, t_free **ptrs)
{
	char	quote;
	int		k;

	k = 0;
	(*dest).value = ft_malloc1(ptrs, calc_cmd_len(src, i) - *i + 1);
	if (!(*dest).value)
		return (0);
	while (src[*i] && !is_whitespace(src[*i]))
	{
		if (src[*i] == '\'' || src[*i] == '\"')
		{
			quote = src[*i];
			(*dest).value[k++] = src[(*i)++];
			while (src[*i] && src[*i] != quote)
				(*dest).value[k++] = src[(*i)++];
		}
		(*dest).value[k++] = src[(*i)++];
	}
	(*dest).value[k++] = '\0';
	return (1);
}

void	get_values_helper(char *input, int *i, t_value *args, t_free **ptrs)
{
	int	j;
	
	j = 0;
	while (input[*i])
	{
		while (input[*i] && is_whitespace(input[*i]))
			(*i)++;
		if (regonize_type(input, *i) != EXPRESSION)
			break ;
		if (input[*i] == '\'' || input[*i] == '\"')
		{
			args[j].value = quoted_cmd(input, i, ptrs);
			j++;
		}
		else
		{
			if (!extract_expr_2(input, args + j, i, ptrs))
				(ft_free_all(ptrs), exit(1));
			j++;
		}
	}
}

t_value *get_values(char *input, int *i, int *args_len, t_free **ptrs)
{
	int j;
	t_value *args;

	j = 0;
	*args_len = calc_args_len(input, *i);
	if (!*args_len)
		return (NULL);
	args = ft_malloc1(ptrs, (*args_len + 1) * sizeof(t_value));
	if (!args)
		(ft_free_all(ptrs), exit(1));
	get_values_helper(input, i, args, ptrs);
	return (args);
}

t_token	*get_cmd(char *input, int *i, int prev_type, t_free **ptrs)
{
	char	*cmd;
	t_token	*new_token;
	int		args_len;

	cmd = NULL;
	if (!extract_expr(input, &cmd, i, ptrs))
		(ft_free_all(ptrs), exit(1));
	new_token = ft_lstnew_1(cmd, regonize_type_2(prev_type),
		get_values(input, i, &args_len, ptrs), ptrs);
	if (!new_token)
		(ft_free_all(ptrs), exit(1));
	new_token->args_len = args_len;
	if (input[*i])
		(*i)--;
	return (new_token);
}
