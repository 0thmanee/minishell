/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboutsli <yboutsli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 03:41:21 by yasser03          #+#    #+#             */
/*   Updated: 2024/03/31 21:54:35 by yboutsli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*int_to_str(int num) 
{
	int len;
    int tmp;
	char *str;

    len = 1;
    tmp = num;
    while (tmp != 0)
    {
        tmp /= 10;
        len++;
    }
    if (num == 0)
        len = 2;
    str = malloc(len + 1);
	str[--len] = '\0';
    while (len)
	{
		str[--len] = (num % 10) + '0';
		num /= 10;
	}
    return (str);
}

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
void	update_exit_status(t_list **list_env, int status)
{
	t_list	*curr;

	if (!list_env)
		return ;
	curr = *list_env;
	while (curr && ft_strcmp(curr->var, "?"))
		curr = curr->next;
	free(curr->value);
	curr->value = int_to_str(status);
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
	printf("status = %d\n", status);
	update_exit_status(list_env, status);
	fd2(fd);
	free(fd);
	return (status);
}
