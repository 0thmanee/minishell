/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboutsli <yboutsli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 16:39:30 by yboutsli          #+#    #+#             */
/*   Updated: 2024/03/28 01:03:55 by yboutsli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int	final_cmd(t_cmd *cmd, t_list **list_env, int io_fd[2])
{
	int 	status;
	int		pid;

	status = 0;
	dup2(io_fd[1], 1);
	close(io_fd[1]);
	pid = new_fork();
	if (pid == 0)
	{
		status = 0;
        handel_io(cmd);
		if (!ft_strcmp(cmd->cmd, "export"))
			status = export(cmd, list_env);
		else if (!ft_strcmp(cmd->cmd, "env"))
			status = env(*list_env);
		else if (!ft_strcmp(cmd->cmd, "cd"))
			status = cd(cmd->args, list_env);
		else if (!ft_strcmp(cmd->cmd, "echo"))
			status = echo(cmd);
		else if (!ft_strcmp(cmd->cmd, "pwd"))
			pwd(list_env);
		else if (!ft_strcmp(cmd->cmd, "unset"))
			unset(list_env, cmd->args);
		else
			status = new_execve(cmd, list_env);
        exit(0);
	}
    dup2(io_fd[1], 1);
	close(io_fd[1]);
	dup2(io_fd[0], 0);
	close(io_fd[0]);
	return (status);
}

int	child_execution(int fd[2], t_cmd *cmd, t_list **list_env)
{
	int		status;

	char	**args;

	dup2(fd[1], 1);
	close2(fd);
    handel_io(cmd);
	status = 0;
	if (!ft_strcmp(cmd->cmd, "export"))
		status = export(cmd, list_env);
	else if (!ft_strcmp(cmd->cmd, "env"))
		status = env(*list_env);
	else if (!ft_strcmp(cmd->cmd, "cd"))
		status = cd(cmd->args, list_env);
	else if (!ft_strcmp(cmd->cmd, "echo"))
		status = echo(cmd);
	else if (!ft_strcmp(cmd->cmd, "pwd"))
		pwd(list_env);
	else if (!ft_strcmp(cmd->cmd, "unset"))
		unset(list_env, cmd->args);
	else
		status = new_execve(cmd, list_env);
	exit(0);		
}

static int middle_cmds(t_cmd *cmd, t_list **list_env, t_free **ptrs)
{
	int status;
	int	fd[2];
	int	pid;
	(void)ptrs;

	status = 0;
	if (pipe(fd) == -1)
	{
		perror("pipe");
		exit(1);
	}
	pid = fork();
	if (pid < 0)
	{
		perror("Fork: ");
		exit(1);
	}
	if (pid == 0)
		status = child_execution(fd, cmd, list_env);
	dup2(fd[0], 0);
	close2(fd);
	return (status);
}

int	execute_2(t_cmd **cmd_list, t_list **list_env, t_free **ptrs, int *io_fd)
{
	t_cmd	*curr;
	int status;

	curr = *cmd_list;
	while (curr->next)
	{
		status = middle_cmds(curr, list_env, ptrs);
		curr = curr->next;
	}
	status = final_cmd(curr, list_env, io_fd);
	while (waitpid(0, 0, 0) != -1)
		;
	return (status);
}