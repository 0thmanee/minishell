/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   final_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouchta <obouchta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 02:23:24 by obouchta          #+#    #+#             */
/*   Updated: 2024/03/17 05:34:07 by obouchta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	final_command(t_token **tokens)
{
	t_token	*curr;
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
		}
		while (curr && curr->type != PIPE)
			curr = curr->next;
		if (curr)
			curr = curr->next;
	}
	return (1);
}
