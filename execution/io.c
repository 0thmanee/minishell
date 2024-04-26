/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouchta <obouchta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 00:03:20 by yboutsli          #+#    #+#             */
/*   Updated: 2024/04/26 15:23:12 by obouchta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_io_infile(t_cmd *cmd, int i)
{
	if (cmd->files[i].is_var && is_ambig(cmd->files[i]))
		return (write(2, "minishell: ambiguous redirect\n", 30),
			1);
	cmd->files[i].fd = open(cmd->files[i].file, O_RDONLY);
	if (cmd->files[i].fd == -1)
		return (write(2, "minishell: ", 11),
			perror(cmd->files[i].file), 1);
	if (cmd->files[i].last_in_out)
		dup2(cmd->files[i].fd, 0);
	close(cmd->files[i].fd);
	return (0);
}

int	handle_io_outfile(t_cmd *cmd, int i, t_free **ptrs)
{
	if (cmd->files[i].is_var && is_ambig(cmd->files[i]))
		return (write(2, "minishell: ambiguous redirect\n", 30), 1);
	if (cmd->files[i].is_var)
		trim_input(&cmd->files[i].file, ptrs);
	if (cmd->files[i].type == 2)
		cmd->files[i].fd = open(cmd->files[i].file,
				O_CREAT | O_TRUNC | O_RDWR, 0644);
	else if (cmd->files[i].type == 3)
		cmd->files[i].fd = open(cmd->files[i].file,
				O_CREAT | O_APPEND | O_RDWR, 0644);
	if (cmd->files[i].fd == -1)
		return (write(2, "minishell: ", 11),
			perror(cmd->files[i].file), 1);
	if (cmd->files[i].last_in_out)
		dup2(cmd->files[i].fd, 1);
	close(cmd->files[i].fd);
	return (0);
}

int	handle_io(t_cmd *cmd, t_free **ptrs)
{
	int	i;

	i = 0;
	if (!cmd->files)
		return (0);
	while (cmd->files[i].fd != -42)
	{
		if (cmd->files[i].type == 0)
		{
			if (handle_io_infile(cmd, i))
				return (1);
		}
		else if (cmd->files[i].type == 2 || cmd->files[i].type == 3)
		{
			if (handle_io_outfile(cmd, i, ptrs))
				return (1);
		}
		i++;
	}
	return (0);
}
