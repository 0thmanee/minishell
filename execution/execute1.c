/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboutsli <yboutsli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 11:49:46 by yboutsli          #+#    #+#             */
/*   Updated: 2024/03/27 17:25:42 by yboutsli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handel_io(t_cmd *cmd)
{
	int	i;

	i = -1;
	if (cmd->infiles)
	{
		while (cmd->infiles[++i].fd != 42)
		{
			if (cmd->infiles[i].type == 0)
			{
				dup2(cmd->infiles[i].fd, 0);
				close(cmd->infiles[i].fd);
				break;
			}
			else if (cmd->infiles[i].type == 1)
			{
				here_doc(cmd);
				break;
			}
		}
	}
	i = -1;
	if (cmd->outfiles)
	{
		while (cmd->outfiles[++i].fd != 42)
		{
			if (cmd->outfiles[i].type == 2)
			{
				dup2(cmd->outfiles[i].fd, 1);
				close(cmd->outfiles[i].fd);
				break;
			}
		}
	}
}


int	child_execve(t_cmd *cmd, t_list **list_env)
{
	int		pid;
	int		status;

	status = 0;
	if (!(cmd->cmd) || !(cmd->cmd[0]))
		return (0);

	pid = fork();
	if (pid == 0)
		status = new_execve(cmd, list_env);
	waitpid(pid, NULL, 0);
	return(status);
}

int	execute_1(t_cmd *cmd, t_list **list_env, t_free **ptrs)
{
	(void)ptrs;
	int		status;

	status = 0;
	handel_io(cmd);
	if (cmd->cmd == NULL)
		return (0);
	if (!ft_strcmp(cmd->cmd, "export"))
		status = export(cmd, list_env);
	else if (!ft_strcmp(cmd->cmd, "env"))
		status = env(*list_env);
	else if (!ft_strcmp(cmd->cmd, "cd"))
		status = cd(cmd->args, list_env);
	else if (!ft_strcmp(cmd->cmd, "echo"))
		status = echo(cmd);
	else if (!ft_strcmp(cmd->cmd, "pwd"))
		pwd();
	else if (!ft_strcmp(cmd->cmd, "unset"))
		unset(list_env, cmd->args);
	else if (!ft_strcmp(cmd->cmd, "exit"))
		exit(0);//to  be eddited to free before exit
	else
		status = child_execve(cmd, list_env);
	return (status);
}
