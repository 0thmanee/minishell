/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_tokens.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouchta <obouchta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 07:21:28 by obouchta          #+#    #+#             */
/*   Updated: 2024/03/07 19:00:42 by obouchta         ###   ########.fr       */
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

t_token	*get_token(char *input, int *i, int type)
{
	int		j;
	char	*value;
	t_token	*new_token;
	int		len;

	j = 0;
	len = 1;
	if (type == APPEND || type == HERE_DOC)
		len = 2;
	value = malloc(len + 1);
	if (!value)
		return (NULL);
	while (input[*i] && !is_whitespace(input[*i]))
		value[j++] = input[(*i)++];
	value[j] = '\0';
	new_token = ft_lstnew_1(value, type, NULL);
	if (!new_token)
		return (NULL);
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
// 	args = get_args(input, i);
// 	new_token = ft_lstnew_1(value, regonize_type_2(prev_type), args);
// 	if (!new_token)
// 		return (NULL);
// 	(*i)--;
// 	return (new_token);
// }