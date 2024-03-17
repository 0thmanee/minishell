/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding_init_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouchta <obouchta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 03:21:04 by obouchta          #+#    #+#             */
/*   Updated: 2024/03/16 03:25:07 by obouchta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_for_var_helper_1(char *value, int *vars, int *i, int *j)
{
	(*i)++;
	while (value[*i] && value[*i] != '\'')
	{
		if (value[*i] == '$')
			vars[(*j)++] = 0;
		(*i)++;
	}
	(*i)++;
}

void	check_for_var_helper_2(char *value, int *vars, int *i, int *j)
{
	(*i)++;
	while (value[*i] && value[*i] != '\"')
	{
		if (value[*i] == '$' && value[(*i) + 1]
			&& value[(*i) + 1] >= '0' && value[(*i) + 1] <= '9')
			vars[(*j)++] = 3;
		else if (value[*i] == '$' && value[(*i) + 1]
			&& value[(*i) + 1] != '\'' && value[(*i) + 1] != '\"')
			vars[(*j)++] = 1;
		else if (value[*i] == '$')
			vars[(*j)++] = 0;
		(*i)++;
	}
	(*i)++;
}

void	check_for_var_helper_3(char *value, int *vars, int *i, int *j)
{
	if (value[(*i) + 1] == '\"' || value[(*i) + 1] == '\'')
		vars[(*j)++] = 2;
	else if (value[(*i) + 1] >= '0' && value[(*i) + 1] <= '9')
		vars[(*j)++] = 3;
	else
		vars[(*j)++] = 1;
	(*i)++;
}