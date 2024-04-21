/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouchta <obouchta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 00:03:20 by yboutsli          #+#    #+#             */
/*   Updated: 2024/04/21 13:11:21 by obouchta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_io_helper1_2(t_cmd *cmd, t_list *list_env, t_free **ptrs, int *io_fd)
{
	int	i;

	i = -1;
	while (cmd->infiles[++i].fd != -42)
	{
		if (cmd->infiles[i].type == 1)
		{
			dup2(io_fd[0], 0);
			if (cmd->infiles[i + 1].fd == -42)
			{
				if (here_doc(cmd->infiles + i, 1, list_env, ptrs))
					return (1);
			}
			else if (here_doc(cmd->infiles + i, 0, list_env, ptrs))
				return (1);
		}
	}
	return (0);
}

int	handle_io_helper1(t_cmd *cmd, t_list *list_env, t_free **ptrs, int *io_fd)
{
	int	i;

	if (handle_io_helper1_2(cmd, list_env, ptrs, io_fd))
		return (-1);
	i = -1;
	while (cmd->infiles[++i].fd != -42)
	{
		if (cmd->infiles[i].type == 0)
		{
			if (cmd->infiles[i].is_var && is_ambig(cmd->infiles[i].file))
				return (write(2, "minishell: ambiguous redirect\n", 30),
					cmd->infiles[i].index);
			cmd->infiles[i].fd = open(cmd->infiles[i].file, O_RDONLY);
			if (cmd->infiles[i].fd == -1)
				return (write(2, "minishell: ", 11),
					perror(cmd->infiles[i].file), cmd->infiles[i].index);
			if (cmd->infiles[i + 1].fd == -42)
				dup2(cmd->infiles[i].fd, 0);
			close(cmd->infiles[i].fd);
		}
	}
	return (-2);
}

int	handle_io_helper2_2(t_cmd *cmd, int *i, t_free **ptrs)
{
	while (cmd->outfiles[*i + 1].fd != -42)
	{
		if (cmd->outfiles[*i].is_var && is_ambig(cmd->outfiles[*i].file))
			return (write(2, "minishell: ambiguous redirect\n", 30), 1);
		if (cmd->outfiles[*i].is_var)
			trim_input(&cmd->outfiles[*i].file, ptrs);
		if (cmd->outfiles[*i].type == 2)
			cmd->outfiles[*i].fd = open(cmd->outfiles[*i].file,
					O_CREAT | O_TRUNC | O_RDWR, 0644);
		else if (cmd->outfiles[*i].type == 3)
			cmd->outfiles[*i].fd = open(cmd->outfiles[*i].file,
					O_CREAT | O_APPEND | O_RDWR, 0644);
		if (cmd->outfiles[*i].fd == -1)
			return (write(2, "minishell: ", 11),
				perror(cmd->outfiles[*i].file), 1);
		(cmd->outfiles[*i].fd != -1 && close(cmd->outfiles[*i].fd));
		(*i)++;
	}
	return (0);
}

int	handle_io_helper2(t_cmd *cmd, t_free **ptrs)
{
	int	i;

	i = 0;
	if (handle_io_helper2_2(cmd, &i, ptrs))
		return (1);
	if (cmd->outfiles[i].is_var && is_ambig(cmd->outfiles[i].file))
		return (write(2, "minishell: ambiguous redirect\n", 30), 1);
	if (cmd->outfiles[i].is_var)
		trim_input(&cmd->outfiles[i].file, ptrs);
	if (cmd->outfiles[i].type == 2)
		cmd->outfiles[i].fd = open((cmd->outfiles[i].file),
				O_CREAT | O_TRUNC | O_RDWR, 0644);
	else if (cmd->outfiles[i].type == 3)
		cmd->outfiles[i].fd = open((cmd->outfiles[i].file),
				O_CREAT | O_APPEND | O_RDWR, 0644);
	if (cmd->outfiles[i].fd != -1)
	{
		dup2(cmd->outfiles[i].fd, 1);
		close(cmd->outfiles[i].fd);
	}
	else
		return (write(2, "minishell: ", 11), perror(cmd->outfiles[i].file), 1);
	return (0);
}

void	open_prev(t_cmd *cmd, int index, t_free **ptrs)
{
	int	i;

	i = 0;
	while (cmd->outfiles[i].fd != -42)
	{
		if (cmd->outfiles[i].index < index)
		{
			if (cmd->outfiles[i].is_var && is_ambig(cmd->outfiles[i].file))
				return ;
			if (cmd->outfiles[i].is_var)
				trim_input(&cmd->outfiles[i].file, ptrs);
			if (cmd->outfiles[i].type == 2)
				cmd->outfiles[i].fd = open(cmd->outfiles[i].file,
						O_CREAT | O_TRUNC | O_RDWR, 0644);
			else if (cmd->outfiles[i].type == 3)
				cmd->outfiles[i].fd = open(cmd->outfiles[i].file,
						O_CREAT | O_APPEND | O_RDWR, 0644);
			if (cmd->outfiles[i].fd == -1)
				return ;
			(cmd->outfiles[i].fd != -1 && close(cmd->outfiles[i].fd));
		}
		i++;
	}
}
