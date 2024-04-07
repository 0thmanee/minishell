/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouchta <obouchta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 11:49:46 by yboutsli          #+#    #+#             */
/*   Updated: 2024/04/07 00:24:26 by obouchta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	env_lc_update(t_cmd *cmd, t_list **list_env, t_free **ptrs)
{
	char	*value;
	char	*new_var;
	int		i;

	i = 0;
	value = NULL;
	if (cmd->args == NULL)
		new_var = cmd->cmd;
	else
	{
		while (cmd->args[i + 1])
			i++;
		new_var = ft_strdup(cmd->args[i], ptrs);
	}
	value = get_env(list_env, "_");
	if (!value)
		ft_lstadd_back_2(list_env, ft_lstnew_2("_", new_var, 0, ptrs));
	else
		env_update(list_env, "_", new_var, ptrs);
}

static int	child_execve(t_cmd *cmd, t_list **list_env, t_free **ptrs)
{
	int		pid;
	int		status;

	status = 0;
	if (!(cmd->cmd) || cmd->io_error)
		return (0);
	pid = fork();
	if (pid == 0)
		new_execve(cmd, list_env, ptrs);
	waitpid(pid, &status, 0);
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
		return (130);
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGQUIT)
		return (131);
	return (WEXITSTATUS(status));
}

static int	execute1_utils(t_cmd *cmd, t_list **list_env, t_free **ptrs)
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
		pwd(list_env);
	else if (!ft_strcmp(cmd->cmd, "exit"))
		ft_exit(cmd, list_env, ptrs);
	else
		status = child_execve(cmd, list_env, ptrs);
	return (status);
}

int	execute_1(t_cmd *cmd, t_list **list_env, t_free **ptrs, int *io_fd)
{
	int		status;

	status = 0;
	if (handle_io(cmd, *list_env, ptrs, io_fd))
		return (1);
	if (cmd->cmd == NULL || cmd->io_error)
		return (0);
	status = execute1_utils(cmd, list_env, ptrs);
	if (ft_strcmp(cmd->cmd, "env"))
		env_lc_update(cmd, list_env, ptrs);
	return (status);
}
