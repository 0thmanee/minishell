/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboutsli <yboutsli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 16:57:06 by yboutsli          #+#    #+#             */
/*   Updated: 2024/03/25 02:57:49 by yboutsli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	null_arg(t_list *list_env)
{
	t_list *current;

	current = list_env;
	while (current)
	{
		printf("declare -x %s", current->var);
		if (current->value)
			printf("=\"%s\"\n", current->value);
		else
			printf("\n");
		current = current->next;
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

void nvalid_output(char *str)
{
	char	*tmp1;
	char	*tmp2;

	tmp1 = ft_strjoin_2("minishell: export: `", str);
	tmp2 = ft_strjoin_2(tmp1, "': not a valid identifier");
	write(2, tmp2, ft_strlen(tmp2));
	write(2, "\n", 1);
	free(tmp1);
	free(tmp2);
}
void	case0(char *str, t_list **list_env)
{
	t_list	*new;

	if (!var_exist(str, *list_env))
		return ;
	new = ft_lstnew_2(str, NULL);
	if (!new)
		exit(1);
	ft_lstadd_back_2(list_env, new);
}
void	case1(char *str, t_list **list_env, int append)
{
	t_list	*new;
	char	*var;
	
	var = ft_substr_2(str, 0, ft_strlen(str) - 1 - append);
	if (!var)
		exit(1);
	if (!var_exist(var, *list_env))
	{
		if (append == 1)
			return ;
		new = get_env_node(list_env, var);
		if (new->value)
			free(new->value);
		new->value = ft_strdup_1("\0");
		free(var);
		return ;
	}
	new = ft_lstnew_2(var, "\0");
	if (!new)
		exit(1);
	ft_lstadd_back_2(list_env, new);
}
void	case2_helper(t_list *new, char *value, int append)
{
	char	*tmp;

	if (new->value)
	{
		if (append == 1)
		{
			tmp = value;
			value = ft_strjoin_2(new->value, value);
			free(tmp);
		}
		free(new->value);
	}
	new->value = value;
}
void	case2(char *str, t_list **list_env, int append)
{
	int	i;
	char	*var;
	char	*value;
	t_list	*new;

	i = 0;
	while (str[i] && str[i] != '=' && str[i] != '+')
		i++;
	var = ft_substr_2(str, 0, i);
	value = ft_substr_2(str, i + 1 + append, ft_strlen(str) - i - 1);
	if (!var_exist(var, *list_env))
	{
		new = get_env_node(list_env, var);
		case2_helper(new, value, append);
		free(var);
		return ;
	}
	new = ft_lstnew_2(var, value);
	free(var);
	free(value);
	if(!new)
		exit(1);
	ft_lstadd_back_2(list_env, new);
}

void	valid_arg(char *str, t_list **list_env)
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
		case0(str, list_env);
	else if (str[i] == '=' && str[i + 1] == '\0')
		case1(str, list_env, append);
	else
		case2(str, list_env, append);
}
int	export(t_cmd *cmd, t_list **list_env)
{
	int	i;
	int	status;

	status = 0;
	i = 0;
	if (cmd->args == NULL)
		null_arg(*list_env);
	else
	{
		while (cmd->args[i])
		{
			if (valid(cmd->args[i]))
				nvalid_output(cmd->args[i]);
			else
				valid_arg(cmd->args[i], list_env);
			i++;
		}
	}
	return (status);
}
