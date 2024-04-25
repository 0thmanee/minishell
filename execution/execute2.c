/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouchta <obouchta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 16:39:30 by yboutsli          #+#    #+#             */
/*   Updated: 2024/04/25 06:31:19 by obouchta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	final_cmd(t_cmd *cmd, t_list **list_env, int io_fd[2], t_free **ptrs)
{
	int	status;
	int	pid;

	dup2(io_fd[1], 1);
	if (cmd->files && handle_io_heredoc(cmd, *list_env, ptrs, io_fd))
		return (1);
	if (handle_io(cmd, ptrs))
		return (1);
	status = 0;
	pid = new_fork();
	if (pid == 0)
	{
		status = 0;
		if (cmd->cmd == NULL)
			exit (0);
		status = child_utils(cmd, list_env, ptrs);
		exit(0);
	}
	dup2(io_fd[1], 1);
	close(io_fd[1]);
	dup2(io_fd[0], 0);
	close(io_fd[0]);
	waitpid(pid, &status, 0);
	return (status);
}

int	has_heredoc(t_cmd *cmd)
{
	int	i;

	i = 0;
	if (!cmd || !cmd->files)
		return (1);
	while (cmd->files[i].fd != -42)
	{
		if (cmd->files[i].type == 1)
			return (0);
		i++;
	}
	return (1);
}

static int	middle_cmds(t_cmd *cmd,
			t_list **list_env, t_free **ptrs, int *io_fd)
{
	int	status;
	int	fd[2];
	int	pid;

	if (cmd->files && handle_io_heredoc(cmd, *list_env, ptrs, io_fd))
		return (1);
	status = 0;
	if (pipe(fd) == -1)
		(write(2, "minishell: ", 11), perror("pipe"), exit(1));
	pid = fork();
	if (pid < 0)
		(write(2, "minishell: ", 11), perror("Fork"), exit(1));
	if (pid == 0)
		status = child_execution(fd, cmd, list_env, ptrs);
	dup2(fd[0], 0);
	close2(fd);
	return (status);
}

int	execute_2(t_cmd **cmd_list, t_list **list_env, t_free **ptrs, int *io_fd)
{
	t_cmd	*curr;
	int		status;

	curr = *cmd_list;
	status = 0;
	while (curr->next)
	{
		status = middle_cmds(curr, list_env, ptrs, io_fd);
		if (status == 1)
			return (status);
		curr = curr->next;
	}
	status = final_cmd(curr, list_env, io_fd, ptrs);
	while (waitpid(0, NULL, 0) != -1)
		;
	return (WEXITSTATUS(status));
}
