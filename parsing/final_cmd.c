/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   final_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouchta <obouchta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 02:23:24 by obouchta          #+#    #+#             */
/*   Updated: 2024/04/21 13:11:35 by obouchta         ###   ########.fr       */
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
			cmd->cmd = ft_strdup(curr->value, ptrs);
			cmd->cmd_is_var = curr->vars_len;
		}
		curr = curr->next;
	}
}

void	index_files_helper1(t_cmd *cmd, int *loc_in, int *in)
{
	if (!cmd->infiles)
		return ;
	cmd->infiles[*loc_in].index = *in;
	(*in)++;
	(*loc_in)++;
}

void	index_files_helper2(t_cmd *cmd, int *loc_in, int *in)
{
	if (!cmd->outfiles)
		return ;
	cmd->outfiles[*loc_in].index = *in;
	(*in)++;
	(*loc_in)++;
}

void	index_files(t_token *token, t_cmd *new_cmd)
{
	t_token	*curr;
	int		index;
	int		in;
	int		out;

	curr = token;
	index = 0;
	in = 0;
	out = 0;
	if (curr && curr->type == PIPE)
		curr = curr->next;
	while (curr && curr->type != PIPE)
	{
		if (curr->type == IN_FILE || curr->type == DELIMITER)
			index_files_helper1(new_cmd, &in, &index);
		if (curr->type == OUT_FILE)
			index_files_helper2(new_cmd, &out, &index);
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
			extract_infiles(curr, new_cmd, ptrs);
			extract_outfiles(curr, new_cmd, ptrs);
			move_options(new_cmd, ptrs);
			index_files(curr, new_cmd);
			ft_lstadd_back_3(command, new_cmd);
			if (curr && curr->type)
				curr = curr->next;
		}
		while (curr && curr->type != PIPE)
			curr = curr->next;
	}
}
