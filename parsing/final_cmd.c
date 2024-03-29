/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   final_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouchta <obouchta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 02:23:24 by obouchta          #+#    #+#             */
/*   Updated: 2024/03/29 03:46:19 by obouchta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_io_error(t_cmd *cmd)
{
	int	i;
	
	if (cmd->infiles)
	{
		i = -1;
		while (cmd->infiles[++i].fd != -42)
		{
			if (cmd->infiles[i].type == 0 && cmd->infiles[i].fd == -1)
				cmd->io_error = 1;
		}
	}
	if (cmd->outfiles && !cmd->io_error)
	{
		i = -1;
		while (cmd->outfiles[++i].fd != -42)
		{
			if (cmd->outfiles[i].fd == -1)
				cmd->io_error = 1;
		}
	}
}

int	final_command(t_token **tokens, t_cmd **command, t_free **ptrs)
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
			extract_args(curr, &(new_cmd->args), ptrs);
			extract_infiles(curr, &(new_cmd->infiles), ptrs);
			extract_outfiles(curr, &(new_cmd->outfiles), ptrs);
			ft_lstadd_back_3(command, new_cmd);
			check_io_error(new_cmd);
			if (curr && curr->type)
				curr = curr->next;
		}
		while (curr && curr->type != PIPE)
			curr = curr->next;
	}
	return (1);
}
