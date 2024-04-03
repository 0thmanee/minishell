/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboutsli <yboutsli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 16:39:30 by yboutsli          #+#    #+#             */
/*   Updated: 2024/04/03 03:54:55 by yboutsli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int	final_cmd(t_cmd *cmd, t_list **list_env, int io_fd[2], t_free **ptrs)
{
	int 	status;
	int		pid;

	if (handle_io(cmd, *list_env, ptrs, io_fd))
		return (1);
	status = 0;
	dup2(io_fd[1], 1);
	close(io_fd[1]);
	pid = new_fork();
	if (pid == 0)
	{
		status = 0;
		if (cmd->cmd == NULL)
			exit (0);
		if (!ft_strcmp(cmd->cmd, "export"))
			status = export(cmd, list_env);
		else if (!ft_strcmp(cmd->cmd, "env"))
			status = env(list_env, cmd);
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

int	has_heredoc(t_cmd *cmd)
{
	int	i;
	
	i = 0;
	if (!cmd || !cmd->infiles)
		return (1);
	while (cmd->infiles[i].fd != -42)
	{
		if (cmd->infiles[i].type == 1)
			return (0);
		i++;
	}
	return (1);
}
int	child_execution(int fd[2], t_cmd *cmd, t_list **list_env, t_free **ptrs)
{
	int		status;

	(void)ptrs;
	dup2(fd[1], 1);
	close2(fd);
	status = 0;
	if (cmd->cmd == NULL)
		exit(0);
	if (!ft_strcmp(cmd->cmd, "export"))
		status = export(cmd, list_env);
	else if (!ft_strcmp(cmd->cmd, "env"))
		status = env(list_env, cmd);
	else if (!ft_strcmp(cmd->cmd, "cd"))
		status = cd(cmd->args, list_env);
	else if (!ft_strcmp(cmd->cmd, "echo"))
		status = echo(cmd);
	else if (!ft_strcmp(cmd->cmd, "pwd"))
		status = pwd(list_env);
	else if (!ft_strcmp(cmd->cmd, "unset"))
		status = unset(list_env, cmd->args);
	else
		status = new_execve(cmd, list_env);
	exit(status);		
}

static int middle_cmds(t_cmd *cmd, t_list **list_env, t_free **ptrs, int *io_fd)
{
	int status;
	int	fd[2];
	int	pid;
	(void)ptrs;

	if (handle_io(cmd, *list_env, ptrs, io_fd))
		return (1);
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
		status = child_execution(fd, cmd, list_env, ptrs);
	//if heredoc wait
	// if (cmd->infiles)
	// {
	// 	int i = 0;
	// 	while (cmd->infiles[i].fd != -42)
	// 	{
	// 		if (cmd->infiles[i].type == 1)
	// 		{
	// 			waitpid(pid, NULL, 0);
	// 			break ;
	// 		}
	// 		i++;
	// 	}
	// }
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
		status = middle_cmds(curr, list_env, ptrs, io_fd);
		if (status == 1)
			return(status);
		curr = curr->next;
	}
	status = final_cmd(curr, list_env, io_fd, ptrs);
	while (waitpid(0, &status, 0) != -1)
		;
	return (WEXITSTATUS(status));
}