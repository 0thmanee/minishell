/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding_init_1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouchta <obouchta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 03:19:46 by obouchta          #+#    #+#             */
/*   Updated: 2024/03/16 03:25:04 by obouchta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	calc_vars(char *str)
{
	int	nbr;
	int	i;

	nbr = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
			nbr++;
		i++;
	}
	return (nbr);
}

void	check_for_var(char *value, int *vars, int len)
{
	int		i;
	int		j;

	(void)vars;
	i = 0;
	j = 0;
	while (i < len)
		vars[i++] = 0;
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

int	specify_vars_helper(t_token *curr)
{
	int	i;

	i = 0;
	while (i < curr->args_len)
	{
		curr->args[i]->vars_len = calc_vars(curr->args[i]->value);
		if (curr->args[i]->vars_len)
			curr->args[i]->vars = malloc(curr->args[i]->vars_len * sizeof(int));
		if (!curr->args[i]->vars)
			return (0);
		check_for_var(curr->args[i]->value, curr->args[i]->vars, curr->args[i]->vars_len);
		i++;
	}
	return (1);
}

int	specify_vars(t_token **tokens)
{
	t_token	*curr;

	curr = *tokens;
	while (curr)
	{
		curr->vars_len = calc_vars(curr->value);
		if (curr->vars_len)
			curr->vars = malloc(curr->vars_len * sizeof(int));
		if (!curr->vars)
			return (0);
		check_for_var(curr->value, curr->vars, curr->vars_len);
		if (curr->args)
			if (!specify_vars_helper(curr))
				return (0);
		curr = curr->next;
	}
	return (1);
}
