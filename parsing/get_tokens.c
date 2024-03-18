/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_tokens.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouchta <obouchta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 07:21:28 by obouchta          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/03/15 23:35:21 by obouchta         ###   ########.fr       */
=======
/*   Updated: 2024/03/17 02:12:29 by obouchta         ###   ########.fr       */
>>>>>>> Othmane
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

char	*quoted_cmd(char *input, int *i)
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
	value = malloc(j - *i + 2);
	if (!value)
		return (NULL);
	j = 0;
	value[j++] = input[(*i)++];
	while (input[*i] && input[*i] != quote)
		value[j++] = input[(*i)++];
	while (input[*i] && !is_whitespace(input[*i]))
		value[j++] = input[(*i)++];
	value[j] = '\0';
	return (value);
}

t_token	*get_in_out_helper(char *input, int *i, t_token **tokens)
{
	t_token *arg;
	char	*arg_value;
	
	arg_value = NULL;
<<<<<<< HEAD
	while (input[*i] && is_whitespace(input[*i]))
		(*i)++;
	if (input[*i] && regonize_type(input, *i) == EXPRESSION)
		if (!extract_expr(input, &arg_value, i))
			return (NULL);
	arg = ft_lstnew_1(arg_value,
		regonize_type_2(get_last_type(*tokens)), NULL);
	if (!arg)
		return (NULL);
	arg->args_len = 0;
=======
	arg = NULL;
	while (input[*i] && is_whitespace(input[*i]))
		(*i)++;
	if (input[*i] && regonize_type(input, *i) == EXPRESSION)
	{
		if (!extract_expr(input, &arg_value, i))
			return (NULL);
		arg = ft_lstnew_1(arg_value,
			regonize_type_2(get_last_type(*tokens)), NULL);
		if (!arg)
			return (NULL);
		arg->args_len = 0;
	}
>>>>>>> Othmane
	return (arg);
}

t_token	*get_in_out(char *input, int *i, int type, t_token **tokens)
{
	int		j;
	char	*tok_value;
	t_token	*new_token;
	t_token	*arg;
	int		len;

	j = 0;
	len = 1;
	if (type == APPEND || type == HERE_DOC)
		len = 2;
	tok_value = malloc(len + 1);
	if (!tok_value)
		return (NULL);
	while (input[*i] && !is_whitespace(input[*i]))
		tok_value[j++] = input[(*i)++];
	tok_value[j] = '\0';
	new_token = ft_lstnew_1(tok_value, type, NULL);
	if (!new_token)
		return (NULL);
	new_token->args_len = 0;
	ft_lstadd_back_1(tokens, new_token);
	if (type == PIPE)
		return (NULL);
	arg = get_in_out_helper(input, i, tokens);
	return (arg);
}

t_token	*get_pipe(char *input, int *i, int type)
{
	int		j;
	char	*tok_value;
	t_token	*new_token;
	int		len;

	j = 0;
	len = 1;
	tok_value = malloc(len + 1);
	if (!tok_value)
		return (NULL);
	while (input[*i] && !is_whitespace(input[*i]))
		tok_value[j++] = input[(*i)++];
	tok_value[j] = '\0';
	new_token = ft_lstnew_1(tok_value, type, NULL);
	if (!new_token)
		return (NULL);
	new_token->args_len = 0;
	return (new_token);
}

// t_token	*get_quoted(char *input, int *i, int prev_type)
// {
// 	char	*value;
// 	t_token	*new_token;
// 	char	**args;

// 	value = quoted_cmd(input, i);
// 	if (!value)
// 		return (NULL);
// 	args = get_values(input, i);
// 	new_token = ft_lstnew_1(value, regonize_type_2(prev_type), args);
// 	if (!new_token)
// 		return (NULL);
// 	(*i)--;
// 	return (new_token);
// }