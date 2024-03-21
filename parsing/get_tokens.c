/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_tokens.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouchta <obouchta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 07:21:28 by obouchta          #+#    #+#             */
/*   Updated: 2024/03/21 05:32:09 by obouchta         ###   ########.fr       */
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

char	*quoted_cmd(char *input, int *i, t_free **ptrs)
{
	int		j;
	int		quote;
	char	*value;

	quote = input[*i];
	j = (*i) + 1;
	while (input[j] && input[j] != quote)
		j++;
	while (input[j] && !is_whitespace(input[j]))
		j++;
	value = ft_malloc1(ptrs, j - *i + 2);
	if (!value)
		(ft_free_all(ptrs), exit(1));
	j = 0;
	value[j++] = input[(*i)++];
	while (input[*i] && input[*i] != quote)
		value[j++] = input[(*i)++];
	while (input[*i] && !is_whitespace(input[*i]))
		value[j++] = input[(*i)++];
	value[j] = '\0';
	return (value);
}

t_token	*get_in_out_helper(char *input, int *i, t_token **tokens, t_free **ptrs)
{
	t_token *arg;
	char	*arg_value;
	
	arg_value = NULL;
	arg = NULL;
	while (input[*i] && is_whitespace(input[*i]))
		(*i)++;
	if (input[*i] && regonize_type(input, *i) == EXPRESSION)
	{
		if (!extract_expr(input, &arg_value, i, ptrs))
			(ft_free_all(ptrs), exit(1));
		arg = ft_lstnew_1(arg_value,
			regonize_type_2(get_last_type(*tokens)), NULL, ptrs);
		if (!arg)
			(ft_free_all(ptrs), exit(1));
		arg->args_len = 0;
	}
	return (arg);
}

t_token	*get_in_out(char *input, int *i, t_token **tokens, t_free **ptrs)
{
	int		j;
	char	*tok_value;
	t_token	*new_token;
	int		len;
	int		type;

	(j = 0, len = 1, type = regonize_type(input, *i));
	if (type == APPEND || type == HERE_DOC)
		len = 2;
	tok_value = ft_malloc1(ptrs, len + 1);
	if (!tok_value)
		(ft_free_all(ptrs), exit(1));
	while (input[*i] && !is_whitespace(input[*i]))
		tok_value[j++] = input[(*i)++];
	tok_value[j] = '\0';
	new_token = ft_lstnew_1(tok_value, type, NULL, ptrs);
	if (!new_token)
		(ft_free_all(ptrs), exit(1));
	new_token->args_len = 0;
	ft_lstadd_back_1(tokens, new_token);
	return (get_in_out_helper(input, i, tokens, ptrs));
}

t_token	*get_pipe(char *input, int *i, int type, t_free **ptrs)
{
	int		j;
	char	*tok_value;
	t_token	*new_token;
	int		len;

	j = 0;
	len = 1;
	tok_value = ft_malloc1(ptrs, len + 1);
	if (!tok_value)
		(ft_free_all(ptrs), exit(1));
	while (input[*i] && !is_whitespace(input[*i]))
		tok_value[j++] = input[(*i)++];
	tok_value[j] = '\0';
	new_token = ft_lstnew_1(tok_value, type, NULL, ptrs);
	if (!new_token)
		(ft_free_all(ptrs), exit(1));
	new_token->args_len = 0;
	return (new_token);
}
