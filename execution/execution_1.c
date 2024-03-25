/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboutsli <yboutsli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 03:41:21 by yasser03          #+#    #+#             */
/*   Updated: 2024/03/25 03:21:25 by yboutsli         ###   ########.fr       */
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

char	**list2tab(t_list *list_env)
{
	char 	**tab;
	t_list *current;
	char	*tmp2;
	int		i;
	char	*tmp1;

	tab = malloc((env_size(list_env) + 1) * sizeof(char *));
	if (!tab)
		return (NULL);
	current = list_env;
	i = 0;
	while (current)
	{
		if (current->var && current->value)
		{
			tmp1 = ft_strjoin_2(current->var, "=");
			tmp2 = ft_strjoin_2(tmp1, current->value);
			free(tmp1);
			tab[i] = malloc((ft_strlen(tmp2) + 1));
			if (!tab[i])
				return (NULL);
			ft_strcpy(tab[i], tmp2);
			i++;
		}
		current = current->next;
	}
	tab[i] = NULL;
	return(tab);
}

int	child_process(t_cmd *cmd, char **args, char *cmd_fpath, t_list **list_env)
{
	char	**env_tab;

	env_tab = list2tab(*list_env);
	if (execve(cmd_fpath, args, env_tab) == -1)
	{
		perror(cmd->cmd);
		return (1);
	}
	return (0);
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

int	execute_execve(t_cmd *cmd, t_list **list_env, char **npath)
{
	int		pid;
	char	*cmd_fpath;
	char	**args;
	int		status;

	status = 0;
	if (!(cmd->cmd) || !(cmd->cmd[0]))
		return (0);
	args = execve_argv(cmd);
	cmd_fpath = cmd_path(cmd->cmd, npath);
	if (!cmd_fpath)
	{
		printf("command not found: %s\n", cmd->cmd);
		return (1);
	}
	pid = fork();
	if (pid == 0)
		status = child_process(cmd, args, cmd_fpath, list_env);
	waitpid(pid, NULL, 0);
	status = 1;
	free(args);
	return(0);
}

int	execute_parent(t_cmd *cmd, t_list **list_env, t_free **ptrs)
{
	(void)ptrs;
	char	**npath;
	int		status;

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
		npath = path(list_env);
		status = execute_execve(cmd, list_env, npath);
	}
	return (status);
}
int	ft_execution(t_cmd **cmd, t_list **list_env, t_free **ptrs)
{
	int	status;

	status = 0;
	if (ft_lstsize(*cmd) == 1)
		status = execute_parent(*cmd, list_env, ptrs);
	if (!ft_strcmp((*cmd)->cmd, "export"))
		export((*cmd), list_env);
	else if (!ft_strcmp((*cmd)->cmd, "env"))
		env(*list_env);
	return (status);
}