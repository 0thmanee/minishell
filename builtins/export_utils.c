/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboutsli <yboutsli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 16:08:36 by yboutsli          #+#    #+#             */
/*   Updated: 2024/04/13 20:54:37 by yboutsli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	valid(char *str)
{
	int	i;

	i = 0;
	if (ft_isalpha(str[0]) && str[0] != '_')
		return (1);
	while (str[i] != '\0' && str[i] != '=' && str[i] != '+')
	{
		if ((ft_isalpha(str[i]) && ft_isdigit(str[i])) && str[i] != '_')
			return (1);
		i++;
	}
	if (str[i] == '+' && str[i + 1] != '=')
		return (1);
	return (0);
}

int	nvalid_output(char *str1, char *str2)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(str2, 2);
	ft_putstr_fd(": `", 2);
	ft_putstr_fd(str1, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
	return (1);
}

static void	alpha_indexing(t_list **list_env)
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
		if (curr[1] && curr[1]->type == 0 && ft_strcmp(curr[1]->var, "_"))
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

void	case0(char *str, t_list **list_env, t_free **ptrs)
{
	if (!var_exist(str, *list_env))
		return ;
	ft_lstadd_back_2(list_env, ft_lstnew_2(str, NULL, 0, ptrs));
}
