/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   final_cmd_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouchta <obouchta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 04:30:01 by obouchta          #+#    #+#             */
/*   Updated: 2024/03/21 07:35:46 by obouchta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	tokens_len(t_token *tokens)
{
	int	len;

	len = 0;
	while (tokens)
	{
		len++;
		tokens = tokens->next;
	}
	return (len);
}

int	extract_command(t_token *token, char **cmd)
{
	t_token	*curr;

	curr = token;
	if (curr && curr->type == PIPE)
		curr = curr->next;
	while (curr && curr->type != PIPE)
	{
		if (curr->type == CMD)
		{
			*cmd = ft_strdup_1(curr->value);
			if (!*cmd)
				return (0);
			return (1);
		}
		curr = curr->next;
	}
	return (1);
}

int	extract_args_helper(t_token *curr, char ***args)
{
	int	j;

	j = 0;
	while (j < curr->args_len)
	{
		(*args)[j] = ft_strdup_1(curr->args[j].value);
		j++;
	}
	(*args)[j] = NULL;
	return (1);
}

int	extract_args(t_token *token, char ***args)
{
	t_token	*curr;
	int		i;

	curr = token;
	i = 0;
	if (curr && curr->type == PIPE)
		curr = curr->next;
	while (curr && curr->type != PIPE)
	{
		if (curr->type == CMD && curr->args_len)
		{
			*args = malloc((curr->args_len + 1) * sizeof(char *));
			if (!*args)
				return (0);
			if (!extract_args_helper(curr, args))
				return (0);
			return (1);
		}
		curr = curr->next;
	}
	return (1);
}
