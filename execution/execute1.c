/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboutsli <yboutsli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 11:49:46 by yboutsli          #+#    #+#             */
/*   Updated: 2024/03/31 05:55:30 by yboutsli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	env_lc_update(t_cmd *cmd, t_list **list_env)
{
	char	*value;
	char	*new;
	char	*cmd_fpath;
	char	**npath;
	int		i;

	if (cmd->args == NULL)
	{
		npath = path(list_env);
		cmd_fpath = cmd_path(cmd->cmd, npath);
		new = cmd_fpath;
		ft_free(npath);
	}
	else
	{
		i = 0;
		while (cmd->args[i + 1])
			i++;
		new = ft_strdup_1(cmd->args[i]);
	}
	value = get_env(list_env, "_");
	if (!value)
		ft_lstadd_back_2(list_env, ft_lstnew_2("_", new));
	else
		env_update(list_env, "_", new);
}

int	handle_io_helper1_2(t_cmd *cmd, t_list *list_env, int *i, t_free **ptrs)
{
	while (cmd->infiles[*i + 1].fd != -42)
	{
		if (cmd->infiles[*i].type == 0)
		{
			cmd->infiles[*i].fd = open(cmd->infiles[*i].file, O_RDONLY);
			if (cmd->infiles[*i].fd == -1)
				cmd->io_error = 1;
			(cmd->infiles[*i].fd != -1 && close(cmd->infiles[*i].fd));
		}
		else if (cmd->infiles[*i].type == 1
			&& here_doc(cmd->infiles + *i, 0, list_env, ptrs))
			return (1);
		(*i)++;
	}
	return (0);
}

int	handle_io_helper1(t_cmd *cmd, t_list *list_env, t_free **ptrs)
{
	int	i;

	i = 0;
	if (handle_io_helper1_2(cmd, list_env, &i, ptrs))
		return (1);
	if (cmd->infiles[i].type == 0)
	{
		cmd->infiles[i].fd = open(cmd->infiles[i].file, O_RDONLY);
		if (cmd->infiles[i].fd == -1)
				cmd->io_error = 1;
		if (cmd->infiles[i].fd != -1)
		{
			(!(cmd->io_error) && dup2(cmd->infiles[i].fd, 0));
			close(cmd->infiles[i].fd);
		}
	}
	else if (cmd->infiles[i].type == 1
		&& here_doc(cmd->infiles + i, !(cmd->io_error), list_env, ptrs))
		return (1);
	return (0);
}

void	handle_io_helper2(t_cmd *cmd)
{
	int	i;

	i = 0;
	while (cmd->outfiles[i + 1].fd != -42)
	{
		if (cmd->outfiles[i].type == 2)
			cmd->outfiles[i].fd = open(cmd->outfiles[i].file, O_CREAT | O_RDWR, 0644);
		else if (cmd->outfiles[i].type == 3)
			cmd->outfiles[i].fd = open(cmd->outfiles[i].file, O_CREAT | O_APPEND, 0644);
		if (cmd->outfiles[i].fd == -1)
			cmd->io_error = 1;
		(cmd->outfiles[i].fd != -1 && close(cmd->outfiles[i].fd));
		i++;
	}
	if (cmd->outfiles[i].type == 2)
		cmd->outfiles[i].fd = open(cmd->outfiles[i].file, O_CREAT | O_RDWR, 0644);
	else if (cmd->outfiles[i].type == 3)
		cmd->outfiles[i].fd = open(cmd->outfiles[i].file, O_CREAT | O_APPEND, 0644);
	if (cmd->outfiles[i].fd != -1)
	{
		(!(cmd->io_error) && dup2(cmd->outfiles[i].fd, 1));
		close(cmd->outfiles[i].fd);
	}
}

int	handle_io(t_cmd *cmd, t_list *list_env, t_free **ptrs)
{
	if (cmd->infiles && handle_io_helper1(cmd, list_env, ptrs))
		return (1);
	if (cmd->outfiles)
		handle_io_helper2(cmd);
	if (cmd->io_error)
		write(2, "minishell: No such file or directory\n", 37);
	return (0);
}


int	child_execve(t_cmd *cmd, t_list **list_env)
{
	int		pid;
	int		status;

	status = 0;
	if (!(cmd->cmd) || !(cmd->cmd[0]) || cmd->io_error)
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
	if (handle_io(cmd, *list_env, ptrs))
		return (1);
	if (cmd->cmd == NULL || cmd->io_error)
		return (0);
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
	else if (!ft_strcmp(cmd->cmd, "exit"))
		ft_exit(cmd);
	else
		status = child_execve(cmd, list_env);
	if (ft_strcmp(cmd->cmd, "env"))
		env_lc_update(cmd, list_env);//lc : last command
	return (status);
}
