/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding_init_1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouchta <obouchta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 03:19:46 by obouchta          #+#    #+#             */
/*   Updated: 2024/04/04 00:39:55 by obouchta         ###   ########.fr       */
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

void	specify_vars_helper(t_token *curr, t_free **ptrs)
{
	int	i;

	i = 0;
	if (!curr->args_len)
		return ;
	while (i < curr->args_len)
	{
		curr->args[i].vars_len = calc_vars(curr->args[i].value);
		if (curr->args[i].vars_len)
		{
			curr->args[i].vars = ft_malloc(ptrs, curr->args[i].vars_len * sizeof(int));
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
		if (curr->vars_len > 0)
		{
			if (curr->type == OUT_FILE || curr->type == IN_FILE)
				curr->is_var = 1;
			curr->vars = ft_malloc(ptrs, curr->vars_len * sizeof(int));
			check_for_var(curr->value, curr->vars, curr->vars_len);
		}
		if (curr->args_len)
			specify_vars_helper(curr, ptrs);
		curr = curr->next;
	}
}
