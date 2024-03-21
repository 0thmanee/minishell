/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_spaces.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouchta <obouchta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 10:57:02 by obouchta          #+#    #+#             */
/*   Updated: 2024/03/20 22:40:38 by obouchta         ###   ########.fr       */
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
	else
		new_input[(*j)++] = input[*i];
}

void	add_spaces(char **input, t_free **ptrs)
{
	int		i;
	int		j;
	int		new_len;
	char	*new_input;
	char	*tmp;

	i = -1;
	new_len = ft_new_len(*input);
	new_input = ft_malloc1(ptrs, new_len + 1);
	if (!new_input)
		(free(*input), exit(1));
	i = -1;
	j = 0;
	while ((*input)[++i])
	{
		if (((*input)[i] == '<' || (*input)[i] == '>') && !quoted((*input), i))
			add_spaces_helper_1(*input, new_input, &i, &j);
		else
			add_spaces_helper_2(*input, new_input, &i, &j);
	}
	new_input[j] = '\0';
	tmp = *input;
	*input = new_input;
	free(tmp);
}
