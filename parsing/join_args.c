/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_args.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouchta <obouchta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 20:15:35 by obouchta          #+#    #+#             */
/*   Updated: 2024/04/05 04:03:11 by obouchta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	remove_token(t_token **head, t_token *node_to_remove, t_free **ptrs)
{
	t_token	*prev;

	prev = *head;
	if (!(*head) || !node_to_remove)
		return ;
	if (*head == node_to_remove)
	{
		*head = node_to_remove->next;
		ft_free_ptr(ptrs, node_to_remove->value);
		ft_free_ptr(ptrs, node_to_remove);
		return ;
	}
	while (prev->next && prev->next != node_to_remove)
		prev = prev->next;
	if (prev->next == NULL)
		return ;
	prev->next = node_to_remove->next;
	ft_free_ptr(ptrs, node_to_remove->value);
	ft_free_ptr(ptrs, node_to_remove);
}

void	fill_args(t_token *cmd, t_value *new_args, int *i, t_free **ptrs)
{
	int	j;

	j = 0;
	if (cmd->args_len)
		while (j < cmd->args_len)
			new_args[(*i)++].value = ft_strdup(cmd->args[j++].value, ptrs);
}

t_value	*collect_args(t_token *cmd, t_token *curr, int *len, t_free **ptrs)
{
	t_value	*new_args;
	int		args_nbr;
	int		i;

	i = 0;
	args_nbr = cmd->args_len + curr->args_len;
	if (curr->type == CMD)
		args_nbr++;
	if (!args_nbr)
		return (NULL);
	new_args = ft_malloc(ptrs, (args_nbr + 1) * sizeof(t_value));
	fill_args(cmd, new_args, &i, ptrs);
	if (curr->type == CMD)
		new_args[i++].value = ft_strdup(curr->value, ptrs);
	fill_args(curr, new_args, &i, ptrs);
	(*len) = i;
	return (new_args);
}

void	join_args_helper(t_token **tokens, t_token **curr,
	t_token **cmd, t_free **ptrs)
{
	t_token	*tmp;

	while (*curr && (*curr)->type != PIPE)
	{
		tmp = *curr;
		(*cmd)->args = collect_args(*cmd, (*curr), &((*cmd)->args_len), ptrs);
		(*curr)->args_len = 0;
		(*curr) = (*curr)->next;
		if (tmp->type == CMD)
			remove_token(tokens, tmp, ptrs);
		else
			ft_free_ptr(ptrs, tmp->args);
	}
}

void	join_args(t_token **tokens, t_free **ptrs)
{
	t_token	*curr;
	t_token	*cmd;

	curr = *tokens;
	while (curr)
	{
		if (curr->type == CMD)
		{
			cmd = curr;
			curr = curr->next;
			join_args_helper(tokens, &curr, &cmd, ptrs);
		}
		else
			curr = curr->next;
	}
}
