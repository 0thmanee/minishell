/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   final_cmd_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouchta <obouchta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 04:30:01 by obouchta          #+#    #+#             */
/*   Updated: 2024/03/22 08:57:26 by obouchta         ###   ########.fr       */
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

void	extract_args_helper(t_token *curr, char ***args, t_free **ptrs)
{
	int	j;

	j = 0;
	while (j < curr->args_len)
	{
		(*args)[j] = ft_strdup(curr->args[j].value, ptrs);
		j++;
	}
	(*args)[j] = NULL;
}

void	extract_args(t_token *token, char ***args, t_free **ptrs)
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
			*args = ft_malloc(ptrs, (curr->args_len + 1) * sizeof(char *));
			if (!*args)
				(ft_free_all(ptrs), exit(1));
			extract_args_helper(curr, args, ptrs);
		}
		curr = curr->next;
	}
}
