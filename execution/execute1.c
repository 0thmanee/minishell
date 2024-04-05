/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboutsli <yboutsli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 11:49:46 by yboutsli          #+#    #+#             */
/*   Updated: 2024/04/05 02:01:08 by yboutsli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	env_lc_update(t_cmd *cmd, t_list **list_env, t_free **ptrs)
{
	char	*value;
	char	*new_var;
	int		i;

	(i = 0, value = NULL);
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

int	handle_io_helper1_2(t_cmd *cmd, t_list *list_env, t_free **ptrs, int *io_fd)
{
	int	i;

	i = -1;
	while (cmd->infiles[++i].fd != -42)
	{
		if (cmd->infiles[i].type == 1)
		{
			dup2(io_fd[1], 1);
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
		return (1);
	i = -1;
	while (cmd->infiles[++i].fd != -42)
	{
		if (cmd->infiles[i].type == 0)
		{
			if (cmd->infiles[i].is_var && is_ambig(cmd->infiles[i].file))
				return (write(2, "minishell: ambiguous redirect\n", 30), 1);
			cmd->infiles[i].fd = open(cmd->infiles[i].file, O_RDONLY);
			if (cmd->infiles[i].fd == -1)
				return (write(2, "minishell: ", 11),
					perror(cmd->infiles[i].file), 1);
			if (cmd->infiles[i + 1].fd == -42)
				dup2(cmd->infiles[i].fd, 0);
			close(cmd->infiles[i].fd);
		}
	}
	return (0);
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
			return (write(2, "minishell: ", 11), perror(cmd->outfiles[*i].file), 1);
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

int	handle_io(t_cmd *cmd, t_list *list_env, t_free **ptrs, int *io_fd)
{
	if (cmd->infiles && handle_io_helper1(cmd, list_env, ptrs, io_fd))
		return (1);
	if (cmd->outfiles && handle_io_helper2(cmd, ptrs))
		return (1);
	return (0);
}

int	child_execve(t_cmd *cmd, t_list **list_env, t_free **ptrs)
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
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGQUIT)
	 	return (131);
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGQUIT)
	 	return (132);
	return (WEXITSTATUS(status));//more study
	return(status);
}

int	execute_1(t_cmd *cmd, t_list **list_env, t_free **ptrs,  int *io_fd)
{
	int		status;

	status = 0;
	if (handle_io(cmd, *list_env, ptrs, io_fd))
		return (1);
	if (cmd->cmd == NULL || cmd->io_error)
		return (0);
	if (!ft_strcmp(cmd->cmd, "export"))
		status = export(cmd, list_env, ptrs);
	else if (!ft_strcmp(cmd->cmd, "env"))
		status = env(list_env, cmd, ptrs);
	else if (!ft_strcmp(cmd->cmd, "cd"))
		status = cd(cmd->args, list_env, ptrs);
	else if (!ft_strcmp(cmd->cmd, "echo"))
		status = echo(cmd);
	else if (!ft_strcmp(cmd->cmd, "pwd"))
		pwd(list_env);
	else if (!ft_strcmp(cmd->cmd, "unset"))
		unset(list_env, cmd->args, ptrs);
	else if (!ft_strcmp(cmd->cmd, "exit"))
		ft_exit(cmd, list_env, ptrs);
	else
		status = child_execve(cmd, list_env, ptrs);
	if (ft_strcmp(cmd->cmd, "env"))
		env_lc_update(cmd, list_env, ptrs);
	return (status);
}
