/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_spaces.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouchta <obouchta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 10:57:02 by obouchta          #+#    #+#             */
/*   Updated: 2024/03/13 20:13:53 by obouchta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_spaces_helper_1(char *input, char *new_input, int *i, int *j)
{
	if ((input[*i] == '<' && input[*i + 1] == '<') ||
	(input[*i] == '>' && input[*i + 1] == '>'))
	{
		if (*i > 0 && !is_whitespace(input[*i - 1]))
			new_input[(*j)++] = ' ';
		new_input[(*j)++] = input[(*i)++];
		new_input[(*j)++] = input[*i];
		if (input[*i + 1] && !is_whitespace(input[*i + 1]))
			new_input[(*j)++] = ' ';
	}
	else
	{
		if (*i > 0 && !is_whitespace(input[*i - 1]))
			new_input[(*j)++] = ' ';
		new_input[(*j)++] = input[*i];
		if (input[*i + 1] && input[*i + 1] != ' ')
			new_input[(*j)++] = ' ';
	}
}

void	add_spaces_helper_2(char *input, char *new_input, int *i, int *j)
{
	if (input[*i] == '|' && !quoted(input, *i))
	{
		if (*i > 0 && !is_whitespace(input[*i - 1]))
			new_input[(*j)++] = ' ';
		new_input[(*j)++] = input[*i];
		if (input[*i + 1] && !is_whitespace(input[*i + 1]))
			new_input[(*j)++] = ' ';
	}
	// else if (input[*i] == '$'  && !quoted(input, *i))
	// {
	// 	if (i > 0 && !is_whitespace(input[*i - 1]))
	// 		new_input[(*j)++] = ' ';
	// 	new_input[(*j)++] = input[*i];
	// }
	else
		new_input[(*j)++] = input[*i];
}

char	*add_spaces(char *input)
{
	int		i;
	int		j;
	int		new_len;
	char	*new_input;

	i = -1;
	new_len = ft_new_len(input);
	new_input = malloc((new_len + 1) * sizeof(char));
	if (!new_input)
		perror("error");
	i = -1;
	j = 0;
	while (input[++i])
	{
		if ((input[i] == '<' || input[i] == '>') && !quoted(input, i))
			add_spaces_helper_1(input, new_input, &i, &j);
		else
			add_spaces_helper_2(input, new_input, &i, &j);
	}
	new_input[j] = '\0';
	return (new_input);
}
