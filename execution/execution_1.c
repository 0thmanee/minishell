/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouchta <obouchta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 03:41:21 by yasser03          #+#    #+#             */
/*   Updated: 2024/03/29 20:55:38 by obouchta         ###   ########.fr       */
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
int new_fork()
{
	int	pid;
	pid = fork();
	if (pid < 0)
	{
		perror("Fork: ");
		exit(1);
	}
	return (pid);
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
		status = execute_2(cmd, list_env, ptrs, fd);
	fd2(fd);
	free(fd);
	return (status);
}