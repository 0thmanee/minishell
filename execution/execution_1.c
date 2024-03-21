/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboutsli <yboutsli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 03:41:21 by yasser03          #+#    #+#             */
/*   Updated: 2024/03/21 05:02:09 by yboutsli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int	env_size(t_list *list_env)
// {
// 	int	count;
// 	t_list *current;

// 	count = 0;
// 	current = list_env;	
// 	while (current)
// 	{
// 		if (current->var && current->value)
// 			count++;
// 		current = current->next;
// 	}
// 	return (count);
// }

// char	**list2tab(t_list *list_env)
// {
// 	char 	**tab;
// 	t_list *current;
// 	char	*tmp2;
// 	int		i;
// 	char	*tmp1;

// 	tab = malloc((env_size(list_env) + 1) * sizeof(char *));
// 	if (!tab)
// 		return (NULL);
// 	current = list_env;
// 	i = 0;
// 	while (current)
// 	{
// 		if (current->var && current->value)
// 		{
// 			tmp1 = ft_strjoin(current->var, "=");
// 			tmp2 = ft_strjoin(tmp1, current->value);
// 			free(tmp1);
// 			tab[i] = malloc((ft_strlen(tmp2) + 1));
// 			if (!tab[i])
// 				return (NULL);
// 			ft_strcpy(tab[i], tmp2);
// 			i++;
// 		}
// 		current = current->next;
// 	}
// 	tab[i] = NULL;
// 	return(tab);
// }
// void	child_process(t_token *token, char **args, char *cmd_fpath, t_list *list_env)
// {
// 	char	**envp;

// 	envp = list2tab(list_env);
// 	if (execve(cmd_fpath, args, envp) == -1)
// 		perror(token->value);
// }
// int	execute_execve(t_token *token, t_list *list_env, char **npath)
// {
// 	int	pid;
// 	(void)list_env;
// 	char	*cmd_fpath;
// 	char	**args;

// 	args = execve_argv(token, npath);
// 	cmd_fpath = cmd_path(token->value, npath);
// 	if (!cmd_fpath)
// 	{
// 		printf("command not found: %s\n", token->value);
// 		return (0);
// 	}
// 	pid = fork();
// 	if (pid == 0)
// 		child_process(token, args, cmd_fpath, list_env);
// 	waitpid(pid, NULL, 0);
// 	free(args);
// 	return(0);
// }
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
// 	if (!ft_strcmp(token->value, "cd"))
// 		cd(token->args, list_env);
// 	else if (!ft_strcmp(token->value, "echo"))
// 		echo(str, *list_env, *list_set);
// 	else if (!ft_strcmp(token->value, "env"))
// 		env(*list_env);
// 	else if (!ft_strcmp(token->value, "pwd"))
// 		pwd();
// 	else
// 		execute_execve(token, *list_env, npath);
// 	free(str);
// 	free(expanded);
// 	return (0);
// }
//0

void	ft_execution(t_cmd *cmd, t_list **list_env)
{
	if (!ft_strcmp(cmd->cmd, "export"))
		export(cmd, list_env);
	else if (!ft_strcmp(cmd->cmd, "env"))
		env(*list_env);
}