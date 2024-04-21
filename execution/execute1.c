/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouchta <obouchta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 11:49:46 by yboutsli          #+#    #+#             */
/*   Updated: 2024/04/21 13:10:58 by obouchta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_io(t_cmd *cmd, t_list *list_env, t_free **ptrs, int *io_fd)
{
	int	index;

	if (cmd->infiles)
	{
		index = handle_io_helper1(cmd, list_env, ptrs, io_fd);
		if (index == -1)
			return (1);
		else if (index >= 0)
		{
			open_prev(cmd, index, ptrs);
			return (1);
		}
	}
	if (cmd->outfiles && handle_io_helper2(cmd, ptrs))
		return (1);
	return (0);
}

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
	value = get_env(list_env, "_", 0, ptrs);
	if (!value)
		ft_lstadd_back_2(list_env, ft_lstnew_2("_", new_var, ptrs));
	else
		env_update(list_env, "_", new_var, ptrs);
}

static int	child_execve(t_cmd *cmd, t_list **list_env,
	struct termios attr, t_free **ptrs)
{
	int				pid;
	int				status;

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
	{
		if (tcsetattr(STDIN_FILENO, TCSANOW, &attr) == -1)
			(ft_free_all(ptrs), exit(1));
		printf("Quit : 3\n");
		return (131);
	}
	return (WEXITSTATUS(status));
}

static int	execute1_utils(t_cmd *cmd, t_list **list_env,
	struct termios attr, t_free **ptrs)
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
		ft_exit(cmd, ptrs, 1);
	else
		status = child_execve(cmd, list_env, attr, ptrs);
	return (status);
}

int	execute_1(t_cmd *cmd, t_list **list_env, t_free **ptrs, int *io_fd)
{
	int				status;
	struct termios	attr;

	status = 0;
	if (tcgetattr(STDIN_FILENO, &attr) == -1)
		(ft_free_all(ptrs), exit(1));
	if (handle_io(cmd, *list_env, ptrs, io_fd))
		return (1);
	if (cmd->cmd == NULL || cmd->io_error)
		return (0);
	status = execute1_utils(cmd, list_env, attr, ptrs);
	if (ft_strcmp(cmd->cmd, "env"))
		env_lc_update(cmd, list_env, ptrs);
	return (status);
}
