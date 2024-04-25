/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   final_cmd_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouchta <obouchta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 04:30:01 by obouchta          #+#    #+#             */
/*   Updated: 2024/04/25 16:17:43 by obouchta         ###   ########.fr       */
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

int	get_cmd_from_args(t_token *curr, t_cmd *cmd, t_free **ptrs)
{
	int	i;
	int	start;

	i = 0;
	start = 0;
	while (i < curr->args_len && !curr->args[i].value
		&& !(!curr->args[i].value && curr->args[i].vars_len
			&& !(curr->args[i].no_quote)))
		i++;
	if (i < curr->args_len)
	{
		if (!curr->args[i].value)
			cmd->cmd = ft_strdup("", ptrs);
		else
			cmd->cmd = ft_strdup(curr->args[i].value, ptrs);
		cmd->cmd_is_var = curr->args[i].vars_len;
		start = i + 1;
	}
	return (start);
}

int	get_new_args_len(t_token *token, int i)
{
	int	len;

	len = 0;
	while (i < token->args_len)
	{
		if (token->args[i].value
			|| (!token->args[i].value && token->args[i].vars_len
				&& !(token->args[i].no_quote)))
			len++;
		i++;
	}
	return (len);
}

void	extract_args_helper(t_token *curr, t_cmd *cmd, int i, t_free **ptrs)
{
	int	new_len;
	int	j;

	new_len = get_new_args_len(curr, i);
	j = 0;
	if (!new_len)
		return ;
	cmd->args = ft_malloc(ptrs, (new_len + 1) * sizeof(char *));
	while (i < curr->args_len)
	{
		if (!curr->args[i].value && curr->args[i].vars_len
			&& !(curr->args[i].no_quote))
		{
			(cmd->args)[j] = ft_strdup("", ptrs);
			j++;
		}
		else if (curr->args[i].value)
		{
			(cmd->args)[j] = ft_strdup(curr->args[i].value, ptrs);
			j++;
		}
		i++;
	}
	(cmd->args)[j] = NULL;
}

void	extract_args(t_token *token, t_cmd *cmd, t_free **ptrs)
{
	t_token	*curr;
	int		i;
	int		start;

	curr = token;
	i = 0;
	start = 0;
	if (curr && curr->type == PIPE)
		curr = curr->next;
	while (curr && curr->type != PIPE)
	{
		if (curr->type == CMD && curr->args_len)
		{
			if (!cmd->cmd)
				start = get_cmd_from_args(curr, cmd, ptrs);
			extract_args_helper(curr, cmd, start, ptrs);
		}
		curr = curr->next;
	}
}
