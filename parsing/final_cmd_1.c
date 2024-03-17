/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   final_cmd_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouchta <obouchta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 04:30:01 by obouchta          #+#    #+#             */
/*   Updated: 2024/03/17 05:21:42 by obouchta         ###   ########.fr       */
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
	while (curr && curr->type != PIPE)
	{
		if (curr->type == CMD)
		{
			*cmd = ft_strdup(curr->value);
			if (!*cmd)
				return (0);
			return (1);
		}
		curr = curr->next;
	}
	return (1);
}

int	extract_args_helper(t_token *curr, char ***args, int *i)
{
	t_value	*curr_arg;

	curr_arg = curr->args;
	while (curr_arg)
	{
		args[*i] = ft_strdup(curr_arg->value);
		if (!args[(*i)++])
			return (0);
		curr_arg = curr_arg->next;
	}
	args[*i]= NULL;
	return (1);
}

int	extract_args(t_token *token, char ***args)
{
	t_token	*curr;
	int		i;

	curr = token;
	i = 0;
	while (curr && curr->type != PIPE)
	{
		if (curr->type == CMD && curr->args_len)
		{
			*args = malloc((curr->args_len + 1) * sizeof(char *));
			if (!*args)
				return (0);
			if (!extract_args_helper(curr, args, &i))
				return (0);
			return (1);
		}
		curr = curr->next;
	}
	return (1);
}
