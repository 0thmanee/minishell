/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboutsli <yboutsli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 03:41:21 by yasser03          #+#    #+#             */
/*   Updated: 2024/03/27 12:33:13 by yboutsli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int	env_size(t_list *list_env)
{
	int	count;
	t_list *current;

	count = 0;
	current = list_env;	
	while (current)
	{
		if (current->var && current->value)
			count++;
		current = current->next;
	}
	return (count);
}





// char *join_args_y(char **args)
// {
// 	int	i;
// 	char	*tmp1;
// 	char	*tmp2;
// 	char	*result;

// 	if (!args || !args[0])
// 		return (NULL);
// 	i = 1;
// 	result = ft_strdup(args[0]);
// 	while (args[i])
// 	{
// 		tmp1 = ft_strjoin(result, " ");
// 		tmp2 = ft_strjoin(tmp1, args[i]);
// 		free(tmp1);
// 		free(result);
// 		result = tmp2;
// 		i++;
// 	}
// 	return (result);
// }
// int	execute(t_token  *token, t_list **list_env, t_list **list_set, char **npath)
// {
// 	char	*str;
// 	char	*expanded;

// 	str = join_args_y(token->args);
// 	expanded = expanding(str, *list_env);
// 	else
// 		execute_execve(token, *list_env, npath);
// 	free(str);
// 	free(expanded);
// 	return (0);
// }



int	child_execution(int fd[2], t_cmd *cmd, t_list **list_env, int io_fd[2])
{
	int		status;
	char	**npath;
	char	*cmd_fpath;
	char	**args;

	close2(io_fd);
	dup2(fd[1], 1);
	close2(fd);
	status = 0;
	if (!(cmd->cmd) || !(cmd->cmd[0]))
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
	else
	{
		args = execve_argv(cmd);
		npath = path(list_env);
		cmd_fpath = cmd_path(cmd->cmd, npath);
		if (!cmd_fpath)
		{
			printf("command not found: %s\n", cmd->cmd);
			exit (1);
		}
		status = new_execve(cmd, args, cmd_fpath, list_env);
	}
	return (status);		
}
int middle_process(t_cmd *cmd, t_list **list_env, t_free **ptrs, int io_fd[2])
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
		status = child_execution(fd, cmd, list_env, io_fd);
	dup2(fd[0], 0);
	close2(fd);
	return (status);
}
int	final_cmd(t_cmd *cmd, t_list **list_env, int io_fd[2])
{
	int 	status;
	char	**npath;
	char	*cmd_fpath;
	char	**args;
	int		pid;
	status = 0;
	dup2(io_fd[1], 1);
	close(io_fd[1]);
	pid = fork();
	if (pid < 0)
	{
		perror("Fork: ");
		exit(1);
	}
	if (pid == 0)
	{
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
			pwd();
		else if (!ft_strcmp(cmd->cmd, "unset"))
			unset(list_env, cmd->args);
		else
		{
			if (!(cmd->cmd) || !(cmd->cmd[0]))
				return (0);
			args = execve_argv(cmd);
			npath = path(list_env);
			cmd_fpath = cmd_path(cmd->cmd, npath);
			if (!cmd_fpath)
			{
				printf("command not found: %s\n", cmd->cmd);
				exit (1);
			}
			status = new_execve(cmd, args, cmd_fpath, list_env);
		}
	}
	dup2(io_fd[0], 0);
	close(io_fd[0]);
	return (status);		
}

int	execute_2(t_cmd **cmd_list, t_list **list_env, t_free **ptrs)
{
	t_cmd	*curr;
	int	io_fd[2];
	int status;

	io_fd[0] = dup(0);
	io_fd[1] = dup(1);
	curr = *cmd_list;
	while (curr->next)
	{
		status = middle_process(curr, list_env, ptrs, io_fd);
		curr = curr->next;
	}
	status = final_cmd(curr, list_env, io_fd);
	while (waitpid(0, 0, 0) != -1)
		;
	return (status);
}
int *fd1(void)
{
	int *tab;

	tab = malloc (sizeof(int) * 2);
	tab[0] = dup(0);
	tab[1] = dup(1);
	return (tab);
}

void	fd2(int tab[2])
{
	dup2(tab[0], 0);
	dup2(tab[1], 1);
	close2(tab);
}

int	ft_execution(t_cmd **cmd, t_list **list_env, t_free **ptrs)
{
	int	status;
	int	*fd;

	fd = fd1();	
	status = 0;
	if (ft_lstsize(*cmd) == 1)
		status = execute_1(*cmd, list_env, ptrs);
	else
		status = execute_2(cmd, list_env, ptrs);
	fd2(fd);
	free(fd);
	return (status);
}