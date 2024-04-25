/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding_init_1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouchta <obouchta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 03:19:46 by obouchta          #+#    #+#             */
/*   Updated: 2024/04/25 02:57:06 by obouchta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	calc_vars(char *str)
{
	int	nbr;
	int	i;
	int	len;

	nbr = 0;
	i = 0;
	if (!str || !str[0])
		return (0);
	len = ft_strlen(str);
	while (i < len)
	{
		if (str[i] == '$')
			nbr++;
		i++;
	}
	return (nbr);
}

int	check_removed_doll(char *value)
{
	int	len;

	if (!value)
		return (0);
	len = ft_strlen(value);
	if (len < 3 || (len >= 3 && value[len - 3] != '$'))
		return (0);
	if ((value[len - 1] == '\'' && value[len - 2] == '\'')
		|| (value[len - 1] == '\"' && value[len - 2] == '\"'))
		return (1);
	return (0);
}

void	check_for_var(char *value, t_var *vars, int len)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (i < len)
		vars[i++].mode = 0;
	i = 0;
	while (value[i])
	{
		if (value[i] == '\'')
			check_for_var_helper_1(value, vars, &i, &j);
		else if (value[i] == '\"')
			check_for_var_helper_2(value, vars, &i, &j);
		else if (value[i] == '$' && value[i + 1])
			check_for_var_helper_3(value, vars, &i, &j);
		else
			i++;
	}
}

void	specify_vars_helper(t_token *curr, t_free **ptrs)
{
	int	i;

	i = 0;
	if (!curr->args_len)
		return ;
	while (i < curr->args_len)
	{
		curr->args[i].removed_doll = check_removed_doll(curr->args[i].value);
		curr->args[i].vars_len = calc_vars(curr->args[i].value);
		if (curr->args[i].vars_len)
		{
			curr->args[i].vars = ft_malloc(ptrs,
					curr->args[i].vars_len * sizeof(t_var));
			check_for_var(curr->args[i].value,
				curr->args[i].vars, curr->args[i].vars_len);
		}
		i++;
	}
	i = 0;
}

void	specify_vars(t_token **tokens, t_free **ptrs)
{
	t_token	*curr;

	curr = *tokens;
	while (curr)
	{
		curr->vars_len = calc_vars(curr->value);
		curr->removed_doll = check_removed_doll(curr->value);
		if (curr->vars_len > 0)
		{
			curr->vars = ft_malloc(ptrs, curr->vars_len * sizeof(t_var));
			check_for_var(curr->value, curr->vars, curr->vars_len);
		}
		if (curr->args_len)
			specify_vars_helper(curr, ptrs);
		curr = curr->next;
	}
}
