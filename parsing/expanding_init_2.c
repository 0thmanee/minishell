/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding_init_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouchta <obouchta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 03:21:04 by obouchta          #+#    #+#             */
/*   Updated: 2024/04/19 18:17:34 by obouchta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	calc_var_size(char *value, int i)
{
	int	j;

	if (!value)
		return (0);
	j = 1;
	if (value[j + i] == '{')
	{
		j++;
		if (value[j + i] == '?')
			return (3);
		while (value[j + i] && value[j + i] != '}')
			j++;
		return (j);
	}
	if (value[j + i] == '?')
		return (2);
	while (!char_is_valid(value[j + i]))
		j++;
	return (j);
}

void	set_exp_value(t_var *var, int *index, int mode, int size)
{
	var[*index].mode = mode;
	var[*index].size = size;
	(*index)++;
}

void	check_for_var_helper_1(char *value, t_var *vars, int *i, int *j)
{
	(*i)++;
	while (value[*i] && value[*i] != '\'')
	{
		if (value[*i] == '$')
			set_exp_value(vars, j, 0, 0);
		(*i)++;
	}
	(*i)++;
}

void	check_for_var_helper_2(char *value, t_var *vars, int *i, int *j)
{
	(*i)++;
	while (value[*i] && value[*i] != '\"')
	{
		if (value[*i] == '$')
		{
			if (is_whitespace(value[(*i) + 1])
				|| value[(*i) + 1] == '\'' || value[(*i) + 1] == '\"')
				set_exp_value(vars, j, 0, 0);
			else if (value[(*i) + 1] && value[*i + 1] == '{')
				set_exp_value(vars, j, 4, calc_var_size(value, *i));
			else if (ft_isalpha(value[*i + 1]) && value[*i + 1] != '_'
				&& value[*i + 1] != '?' && ft_isdigit(value[*i + 1]))
				set_exp_value(vars, j, 0, calc_var_size(value, *i));
			else if (!ft_isdigit(value[*i + 1]))
				set_exp_value(vars, j, 3, calc_var_size(value, *i));
			else if (value[(*i) + 1])
				set_exp_value(vars, j, 1, calc_var_size(value, *i));
			else
				set_exp_value(vars, j, 0, 0);
		}
		(*i)++;
	}
	(*i)++;
}

void	check_for_var_helper_3(char *value, t_var *vars, int *i, int *j)
{
	if (value[(*i) + 1] == '\"' || value[(*i) + 1] == '\'')
		set_exp_value(vars, j, 2, calc_var_size(value, *i));
	else if (value[(*i) + 1] && value[*i + 1] == '{')
		set_exp_value(vars, j, 4, calc_var_size(value, *i));
	else if (ft_isalpha(value[*i + 1]) && value[*i + 1] != '_'
		&& value[*i + 1] != '?' && ft_isdigit(value[*i + 1]))
		set_exp_value(vars, j, 0, 0);
	else if (!ft_isdigit(value[*i + 1]))
		set_exp_value(vars, j, 3, calc_var_size(value, *i));
	else
		set_exp_value(vars, j, 1, calc_var_size(value, *i));
	(*i)++;
}
