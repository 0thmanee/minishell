/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouchta <obouchta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 20:29:05 by yboutsli          #+#    #+#             */
/*   Updated: 2024/04/14 15:44:31 by obouchta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env(t_list **head, char *env_var, int is_exit, t_free **ptrs)
{
	t_list	*current;

	if (is_exit)
		return (int_to_str(exit_status(1, -1), ptrs));
	if (!head)
		return (NULL);
	current = *head;
	while (current)
	{
		if (!ft_strcmp(current->var, env_var))
			return (current->value);
		current = current->next;
	}
	return (NULL);
}

int	env_update(t_list **head, char *env_var, char *new, t_free **ptrs)
{
	t_list	*current;

	current = *head;
	while (current)
	{
		if (!ft_strcmp(current->var, env_var) && current->type == 0)
		{
			ft_free_ptr(ptrs, current->value);
			current->value = ft_strdup(new, ptrs);
			return (0);
		}
		current = current->next;
	}
	if (!current)
		ft_lstadd_back_2(head, ft_lstnew_2(env_var, new, 0, ptrs));
	return (1);
}

void	env_init(t_list	**env, t_free **ptrs)
{
	char	*cwd;
	char	*tmp;
	t_list	*new_node;

	cwd = getcwd(NULL, 0);
	if (cwd != NULL)
	{
		ft_lstadd_back_2(env, ft_lstnew_2("PATH",
				"/usr/gnu/bin:/usr/local/bin:/bin:/usr/bin:.", 1, ptrs));
		new_node = ft_lstnew_2("PWD", cwd, 0, ptrs);
		ft_lstadd_back_2(env, new_node);
		tmp = ft_strjoin(cwd, "/./minishell", ptrs);
		ft_lstadd_back_2(env, ft_lstnew_2("_", tmp, 0, ptrs));
		ft_lstadd_back_2(env, ft_lstnew_2("OLDPWD", NULL, 0, ptrs));
		ft_free_ptr(ptrs, tmp);
	}
	ft_lstadd_back_2(env, ft_lstnew_2("SHLVL", "1", 0, ptrs));
	free(cwd);
}

int	var_exist(char *var, t_list *list_env)
{
	t_list	*curr;

	curr = list_env;
	while (curr)
	{
		if (!ft_strcmp(curr->var, var) && curr->type == 0)
			return (0);
		curr = curr->next;
	}
	return (1);
}

t_list	*get_env_node(t_list **list_env, char *var)
{
	t_list	*curr;

	curr = *list_env;
	while (curr)
	{
		if (!ft_strcmp(curr->var, var) && curr->type == 0)
			return (curr);
		curr = curr->next;
	}
	return (NULL);
}
