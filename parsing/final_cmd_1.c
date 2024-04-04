/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   final_cmd_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouchta <obouchta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 04:30:01 by obouchta          #+#    #+#             */
/*   Updated: 2024/04/04 21:10:23 by obouchta         ###   ########.fr       */
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

void	extract_command(t_token *token, char **cmd, t_free **ptrs)
{
	t_token	*curr;

	curr = token;
	if (curr && curr->type == PIPE)
		curr = curr->next;
	while (curr && curr->type != PIPE)
	{
		if (curr->type == CMD)
			*cmd = ft_strdup(curr->value, ptrs);
		curr = curr->next;
	}
}

void	get_cmd_from_args(t_token *curr, char **cmd, int *start, t_free **ptrs)
{
	int	i;

	i = 0;
	while (i < curr->args_len && !curr->args[i].value)
		i++;
	if (i < curr->args_len)
	{
		*cmd = ft_strdup(curr->args[i].value, ptrs);
		*start = i + 1;
	}
}

int	get_new_args_len(t_token *token, int i)
{
	int	len;

	len = 0;
	while (i < token->args_len)
	{
		if (token->args[i].value)
			len++;
		i++;
	}
	return (len);
}

void	extract_args_helper(t_token *curr, char ***args, int i, t_free **ptrs)
{
	int	new_len;
	int	j;

	new_len = get_new_args_len(curr, i);
	j = 0;
	if (!new_len)
		return ;
	*args = ft_malloc(ptrs, (new_len + 1) * sizeof(char *));
	while (i < curr->args_len)
	{
		if (curr->args[i].value)
		{
			(*args)[j] = ft_strdup(curr->args[i].value, ptrs);
			j++;
		}
		i++;
	}
	(*args)[j] = NULL;
}

void	extract_args(t_token *token, char ***args, char **cmd, t_free **ptrs)
{
	t_token	*curr;
	int		i;
	int		start;
	

	(curr = token, start = 0, i = 0);
	if (curr && curr->type == PIPE)
		curr = curr->next;
	while (curr && curr->type != PIPE)
	{
		if (curr->type == CMD && curr->args_len)
		{
			if (!(*cmd))
				get_cmd_from_args(curr, cmd, &start, ptrs);
			extract_args_helper(curr, args, start, ptrs);
		}
		curr = curr->next;
	}
}
