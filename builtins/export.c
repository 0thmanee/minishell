/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboutsli <yboutsli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 16:57:06 by yboutsli          #+#    #+#             */
/*   Updated: 2024/04/05 02:10:16 by yboutsli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	alpha_indexing(t_list **list_env)
{
	t_list	*curr[2];
	int		count;

	curr[0] = *list_env;
	while (curr[0])
	{
		curr[1] = *list_env;
		count = 0;
		while (curr[1])
		{
			if (ft_strcmp(curr[0]->var, curr[1]->var) > 0)
				count++;
			curr[1] = curr[1]->next;
		}
		curr[0]->index = count;
		curr[0] = curr[0]->next;
	}
}

void	null_arg(t_list **list_env)
{
	t_list	*curr[2];
	int		count;

	if (!list_env)
		return ;
	alpha_indexing(list_env);
	curr[0] = *list_env;
	count = 0;
	while (curr[0])
	{
		curr[1] = *list_env;
		while (curr[1] && curr[1]->index != count)
			curr[1] = curr[1]->next;
		if(curr[1] && curr[1]->type == 0 && ft_strcmp(curr[1]->value, "_"))
		{
			printf("declare -x %s", curr[1]->var);
			if (curr[1]->value)
				printf("=\"%s\"\n", curr[1]->value);
			else
				printf("\n");
		}			
		curr[0] = curr[0]->next;
		count++;
	}
}

int	valid(char *str)
{
	int	i;

	i = 0;
	if (ft_isalpha(str[0]) && str[0] != '_')
		return (1);
	while (str[i] != '\0' && str[i] != '=' && str[i] != '+')
	{
		if (!ft_isdigit(str[i]) && str[i] != '_')
			return (1);
		i++;
	}
	if (str[i] == '+' && str[i + 1] != '=')
		return (1);
	return (0);
}

void nvalid_output(char *str1, char *str2)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(str2, 2);
	ft_putstr_fd(": `", 2);
	ft_putstr_fd(str1, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
}
void	case0(char *str, t_list **list_env, t_free **ptrs)
{
	if (!var_exist(str, *list_env))
		return ;
	ft_lstadd_back_2(list_env, ft_lstnew_2(str, NULL, 0, ptrs));
}
void	case1(char *str, t_list **list_env, int append, t_free **ptrs)
{
	char	*var;
	t_list	*new_node;
	
	var = ft_substr(str, 0, ft_strlen(str) - 1 - append, ptrs);
	if (!var_exist(var, *list_env))
	{
		if (append == 1)
			return ;
		new_node = get_env_node(list_env, var);
		if (new_node->value)
			ft_free_ptr(ptrs, new_node->value);
		new_node->value = ft_strdup("\0", ptrs);
		ft_free_ptr(ptrs, var);
		return ;
	}
	ft_lstadd_back_2(list_env, ft_lstnew_2(var, "\0", 0, ptrs));
}
void	case2_helper(t_list *new, char *value, int append, t_free **ptrs)
{
	char	*tmp;

	if (new->value)
	{
		if (append == 1)
		{
			tmp = value;
			value = ft_strjoin(new->value, value, ptrs);
			ft_free_ptr(ptrs, tmp);
		}
		ft_free_ptr(ptrs, new->value);
	}
	new->value = value;
}
void	case2(char *str, t_list **list_env, int append, t_free **ptrs)
{
	int	i;
	char	*var;
	char	*value;
	t_list	*new_node;

	i = 0;
	while (str[i] && str[i] != '=' && str[i] != '+')
		i++;
	var = ft_substr(str, 0, i, ptrs);
	value = ft_substr(str, i + 1 + append, ft_strlen(str) - i - 1, ptrs);
	if (!var_exist(var, *list_env))
	{
		new_node = get_env_node(list_env, var);
		case2_helper(new_node, value, append, ptrs);
		ft_free_ptr(ptrs, var);
		return ;
	}
	ft_lstadd_back_2(list_env, ft_lstnew_2(var, value, 0, ptrs));
}

void	valid_arg(char *str, t_list **list_env, t_free **ptrs)
{
	int	i;
	int	append;

	append = 0;
	i = 0;
	while (str[i] && str[i] != '=' && str[i] != '+')
		i++;
	if (str[i] == '+')
	{
		append = 1;
		i++;
	}
	if (!str[i])
		case0(str, list_env, ptrs);
	else if (str[i] == '=' && str[i + 1] == '\0')
		case1(str, list_env, append, ptrs);
	else
		case2(str, list_env, append, ptrs);
}
int	export(t_cmd *cmd, t_list **list_env, t_free **ptrs)
{
	int	i;
	int	status;

	status = 0;
	i = -1;
	if (cmd->args == NULL)
		null_arg(list_env);
	else
	{
		while (cmd->args[++i])
		{
			if (!ft_strcmp(cmd->args[i], "_"))
				continue;
			else if (valid(cmd->args[i]))
			{
				nvalid_output(cmd->args[i], "export");
				status = 1;
			}
			else
				valid_arg(cmd->args[i], list_env, ptrs);
		}
	}
	return (status);
}
