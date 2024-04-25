/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   final_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouchta <obouchta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 02:23:24 by obouchta          #+#    #+#             */
/*   Updated: 2024/04/25 06:24:01 by obouchta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	extract_command(t_token *token, t_cmd *cmd, t_free **ptrs)
{
	t_token	*curr;

	curr = token;
	if (curr && curr->type == PIPE)
		curr = curr->next;
	while (curr && curr->type != PIPE)
	{
		if (curr->type == CMD)
		{
			if (!curr->value && curr->vars_len && !(curr->no_quote))
				cmd->cmd = ft_strdup("", ptrs);
			else
				cmd->cmd = ft_strdup(curr->value, ptrs);
			cmd->cmd_is_var = curr->vars_len;
		}
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
			extract_command(curr, new_cmd, ptrs);
			extract_args(curr, new_cmd, ptrs);
			extract_files(curr, new_cmd, ptrs);
			move_options(new_cmd, ptrs);
			ft_lstadd_back_3(command, new_cmd);
			if (curr && curr->type)
				curr = curr->next;
		}
		while (curr && curr->type != PIPE)
			curr = curr->next;
	}
}
