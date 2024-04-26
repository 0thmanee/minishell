/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute2_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboutsli <yboutsli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 23:00:44 by yboutsli          #+#    #+#             */
/*   Updated: 2024/04/26 17:51:43 by yboutsli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	child_utils(t_cmd *cmd, t_list **list_env, t_free **ptrs)
{
	int	status;

	status = 0;
	if (!ft_strcmp(cmd->cmd, "export"))
		status = export(cmd, list_env, ptrs);
	else if (!ft_strcmp(cmd->cmd, "env"))
		status = env(list_env, cmd, ptrs);
	else if (!ft_strcmp(cmd->cmd, "cd"))
		status = cd(cmd->args, list_env, ptrs);
	else if (!ft_strcmp(cmd->cmd, "echo"))
		status = echo(cmd);
	else if (!ft_strcmp(cmd->cmd, "unset"))
		status = unset(list_env, cmd->args, ptrs);
	else if (!ft_strcmp(cmd->cmd, "pwd"))
		pwd(list_env, ptrs);
	else if (!ft_strcmp(cmd->cmd, "exit"))
		ft_exit(cmd, ptrs, 0);
	else
		status = new_execve(cmd, list_env, ptrs);
	return (status);
}

int	child_execution(int fd[2], t_cmd *cmd, t_list **list_env, t_free **ptrs)
{
	int	status;
	int	mode;

	mode = 0;
	dup2(fd[1], 1);
	if (cmd->files)
		mode = handle_io(cmd, ptrs);
	close2(fd);
	status = 0;
	if (cmd->cmd == NULL)
		exit(0);
	if (!mode)
		status = child_utils(cmd, list_env, ptrs);
	exit(status);
}
