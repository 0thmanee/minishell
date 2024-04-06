/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   final_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouchta <obouchta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 02:23:24 by obouchta          #+#    #+#             */
/*   Updated: 2024/04/06 06:41:54 by obouchta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	final_command(t_token **tokens, t_cmd **command, t_free **ptrs)
{
	t_token	*curr;
	t_cmd	*new_cmd;

	curr = *tokens;
	while (curr)
	{
		if (curr == *tokens || curr->type == PIPE)
		{
			new_cmd = ft_lstnew_3(ptrs);
			extract_command(curr, &(new_cmd->cmd), ptrs);
			extract_args(curr, &(new_cmd->args), &(new_cmd->cmd), ptrs);
			extract_infiles(curr, &(new_cmd->infiles), ptrs);
			extract_outfiles(curr, &(new_cmd->outfiles), ptrs);
			ft_lstadd_back_3(command, new_cmd);
			if (curr && curr->type)
				curr = curr->next;
		}
		while (curr && curr->type != PIPE)
			curr = curr->next;
	}
}
