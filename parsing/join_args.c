/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_args.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouchta <obouchta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 20:15:35 by obouchta          #+#    #+#             */
/*   Updated: 2024/03/15 05:02:48 by obouchta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	fill_args_helper(t_token *cmd, t_arg **new_args, int *i)
{
	int	j;

	j = 0;
	if (cmd->args_len)
		while (j < cmd->args_len)
		{
			new_args[*i] = malloc(sizeof(t_arg));
			if (!new_args[*i])
				return (0);
			new_args[*i]->value = ft_strdup(cmd->args[j]->value);
			if (!new_args[*i]->value)
				return (0);
			(*i)++;
			j++;
		}
	return (1);
}
int	fill_args(t_token *cmd, t_token *curr, int *len, t_arg **new_args)
{
	int	i;

	i = 0;
	if (!cmd->args_len && !curr->args_len)
		return (0);
	if (!fill_args_helper(cmd, new_args, &i))
		return (0);
	if (!fill_args_helper(curr, new_args, &i))
		return (0);
	(*len) = i;
	new_args[i] = NULL;
	return (1);
}

t_arg	**join_args_helper(t_token *cmd, t_token *curr, int *len)
{
	t_arg	**new_args;
	
	if (!(cmd->args_len + curr->args_len))
		return (NULL);
	new_args = malloc((cmd->args_len + curr->args_len + 1) * sizeof(t_arg *));
	if (!new_args)
		return (NULL);
	if (!fill_args(cmd, curr, len, new_args))
		return (NULL);
	return (new_args);
}

void	free_old_args(t_arg ***args)
{
	int	i;

	i = 0;
	if ((*args))
	{
		while ((*args)[i])
		{
			free((*args)[i]);
			i++;
		}
		free((*args));
		(*args) = NULL;
	}
}

int	join_args(t_token **tokens)
{
	t_token	*curr;
	t_token	*cmd;
	t_arg	**tmp;

	curr = *tokens;
	while (curr)
	{
		if (curr->type == CMD)
		{
			(cmd = curr, curr = curr->next);
			while (curr && curr->type != PIPE)
			{
				tmp = cmd->args;
				cmd->args = join_args_helper(cmd, curr, &cmd->args_len);
				curr->args_len = 0;
				(free_old_args(&curr->args), free_old_args(&tmp));
				curr = curr->next;
			}
		}
		else
			curr = curr->next;
	}
	return (1);
}
