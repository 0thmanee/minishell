/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboutsli <yboutsli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 03:41:21 by yasser03          #+#    #+#             */
/*   Updated: 2024/03/14 17:11:37 by yboutsli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	child_process(t_token *token, char **args, char *cmd_fpath)
{

	if (execve(cmd_fpath, args, NULL) == -1)
		perror(token->value);
}
int	execute_execve(t_token *token, t_list *list_env, char **npath)
{
	int	pid;
	(void)list_env;
	char	*cmd_fpath;
	char	**args;

	args = execve_argv(token, npath);
	cmd_fpath = cmd_path(token->value, npath);
	if (!cmd_fpath)
	{
		printf("command not found: %s\n", token->value);
		return (0);
	}
	pid = fork();
	if (pid == 0)
		child_process(token, args, cmd_fpath);
	waitpid(pid, NULL, 0);
	free(args);
	return(0);
}
int	execute(t_token  *token, t_list **list_env, t_list **list_set, char **npath)
{
	if (!ft_strcmp(token->value, "cd"))
		cd(token->args, list_env);
	else if (!ft_strcmp(token->value, "echo"))
		echo(token->args[0], 1, *list_env, *list_set);
	else if (!ft_strcmp(token->value, "env"))
		env(*list_env);
	else if (!ft_strcmp(token->value, "pwd"))
		pwd();
	else
		execute_execve(token, *list_env, npath);
	return (0);
}

void    ft_execution(t_token *token, t_list **env, t_list **set)
{
	t_token *current;

	char **npath;
	npath = path(env);
    // print_the_shit(token);
	current = token;
	while (current)
	{
		if (current->type == CMD)
			execute(token, env, set, npath);
		current = current->next;
	}
	ft_free(npath);
}