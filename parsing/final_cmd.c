/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   final_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouchta <obouchta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 02:23:24 by obouchta          #+#    #+#             */
/*   Updated: 2024/03/20 03:33:14 by obouchta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	final_command(t_token **tokens, t_cmd **command)
{
	t_token	*curr;
	t_cmd	*new_cmd;
	char	*cmd;
	char	**args;
	t_file	*infiles;
	t_file	*outfiles;

	curr = *tokens;
	while (curr)
	{
		if (curr == *tokens || curr->type == PIPE)
		{
			(cmd = NULL, args = NULL, infiles = NULL, outfiles = NULL);
			if (!extract_command(curr, &cmd) || !extract_args(curr, &args)
				|| !extract_infiles(curr, &infiles)|| !extract_outfiles(curr, &outfiles))
				return (0);
			new_cmd = ft_lstnew_3(cmd, args, infiles, outfiles);
			if (!new_cmd)
				return (0);
			ft_lstadd_back_3(command, new_cmd);
			if (curr && curr->type)
				curr = curr->next;
		}
		while (curr && curr->type != PIPE)
			curr = curr->next;
	}
	return (1);
}
