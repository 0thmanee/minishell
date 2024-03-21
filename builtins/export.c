/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboutsli <yboutsli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 16:57:06 by yboutsli          #+#    #+#             */
/*   Updated: 2024/03/21 06:11:33 by yboutsli         ###   ########.fr       */
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

int valid(char *str)
{
	int	i;

	i = 0;
	if (ft_isalpha(str[0]) && str[0] != '_')
		return (1);
	while (str[i] != '\0' && str[i] != '=')
	{
		if (ft_isdigit(str[i]) && str[i] != '_')
			return (1);
		i++;
    }
    return (0);
}

void nvalid_output(char *str)
{
	char	*tmp1;
	char	*tmp2;

	tmp1 = ft_strjoin("minishell: export: `", str);
	tmp2 = ft_strjoin(tmp1, "': not a valid identifier");
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
void	case1(char *str, t_list **list_env)
{
	t_list	*new;
	char	*var;

	var = ft_substr(str, 0, ft_strlen(str) - 1);
	if (!var)
		exit(1);
	if (!var_exist(var, *list_env))
	{
		new = get_env_node(list_env, var);
		if (new->value)
			free(new->value);
		new->value = ft_strdup("\0");
		free(var);
		return ;
	}
	new = ft_lstnew_2(var, "\0");
	if (!new)
		exit(1);
	ft_lstadd_back_2(list_env, new);
}

void	case2(char *str, t_list **list_env)
{
	int	i;
	char	*var;
	char	*value;
	t_list	*new;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	var = ft_substr(str, 0, i);
	value = ft_substr(str, i + 1, ft_strlen(str) - i - 1);
	if (!var_exist(var, *list_env))
	{
		new = get_env_node(list_env, var);
		if (new->value)
			free(new->value);
		new->value = value;	
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

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	if (!str[i])
		case0(str, list_env);
	else if (str[i] == '=' && str[i + 1] == '\0')
		case1(str, list_env);
	else
		case2(str, list_env);
}
void	export(t_cmd *cmd, t_list **list_env)
{
	int	i;

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
}
