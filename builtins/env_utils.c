/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboutsli <yboutsli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 20:29:05 by yboutsli          #+#    #+#             */
/*   Updated: 2024/03/24 16:10:58 by yboutsli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*env_lst(char **envp)
{
	int		i;
	int		j;
	char	*var;
	char	*value;
	t_list	*env;

	env = NULL;
	i = -1;
	while (envp[++i])
	{
		if (!ft_strncmp(envp[i], "OLDPWD", 6))
			continue;
		j = 0;
		while (envp[i][j] && envp[i][j] != '=')	
			j++;
		var = ft_substr_2(envp[i], 0, j);
		value = ft_substr_2(envp[i], j + 1, ft_strlen(envp[i]));
		ft_lstadd_back_2(&env, ft_lstnew_2(var, value));
		free(var);
		free(value);
	}
	if (i > 6)
	{
		var = "OLDPWD";
		value = get_env(&env, "PWD");
		ft_lstadd_back_2(&env, ft_lstnew_2(var, value));
	}
	else
		ft_lstadd_back_2(&env, ft_lstnew_2(var, NULL));
	return (env);
}

char	*get_env(t_list **head, char *env_var)
{
	t_list	*current;

	current = *head;
	while (current)
	{
		if (!ft_strcmp(current->var, env_var))
			return (current->value);
		current = current->next;
	}
	return (NULL);
}

int	env_update(t_list **head, char *env_var, char *new)
{
	t_list	*current;

	current = *head;
	while (current)
	{
		if (!ft_strcmp(current->var, env_var))
		{
			free(current->value);
			current->value = ft_strdup_1(new);
			// printf("|%s=%s|\n", current->var,current->value);
			return (0);
		}
		current = current->next;
	}
	ft_lstadd_back_2(head, ft_lstnew_2(env_var, new));
	return (1);
}

void	env_init(t_list	**env)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	ft_lstadd_back_2(env, ft_lstnew_2("PWD", cwd));
	free(cwd);
}
int	var_exist(char *var, t_list *list_env)
{
	t_list	*current;

	current = list_env;
	while (current)
	{
		if (!ft_strcmp(current->var, var))
			return (0);
		current = current->next;
	}
	return (1);
}

t_list *get_env_node(t_list **list_env, char *var)
{
	t_list	*current;

	current = *list_env;
	while (current)
	{
		if (!ft_strcmp(current->var, var))
			return (current);
		current = current->next;
	}
	return (NULL);	
}
