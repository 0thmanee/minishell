/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboutsli <yboutsli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 16:57:06 by yboutsli          #+#    #+#             */
/*   Updated: 2024/04/05 16:13:54 by yboutsli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	case1(char *str, t_list **list_env, int append, t_free **ptrs)
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

static void	case2_helper(t_list *new, char *value, int append, t_free **ptrs)
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

static void	case2(char *str, t_list **list_env, int append, t_free **ptrs)
{
	int		i;
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

static void	valid_arg(char *str, t_list **list_env, t_free **ptrs)
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
				continue ;
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
