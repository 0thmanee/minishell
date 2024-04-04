/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   final_cmd_3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouchta <obouchta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 05:23:00 by obouchta          #+#    #+#             */
/*   Updated: 2024/04/04 00:40:07 by obouchta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	outfiles_len(t_token *curr)
{
	int	len;

	len = 0;
	while (curr && curr->type != PIPE)
	{
		if (curr->type == OUT_FILE)
			len++;
		curr = curr->next;
	}
	return (len);
}

int	extract_outfiles_helper_1(t_token *curr, t_file **outfiles, int *i, t_free **ptrs)
{
	(*outfiles)[*i].file = ft_strdup(curr->value, ptrs);
	(*outfiles)[*i].fd = -1;
	(*outfiles)[*i].type = 2;
	(*outfiles)[*i].delim_flag = 0;
	(*outfiles)[*i].is_var = curr->is_var;
	(*i)++;
	return (1);
}

int	extract_outfiles_helper_2(t_token *curr, t_file **outfiles, int *i, t_free **ptrs)
{
	(*outfiles)[*i].file = ft_strdup(curr->value, ptrs);
	(*outfiles)[*i].fd = -1;
	(*outfiles)[*i].type = 3;
	(*outfiles)[*i].delim_flag = 0;
	(*outfiles)[*i].is_var = curr->is_var;
	(*i)++;
	return (1);
}

// int	extract_outfiles_helper(t_token **curr, t_file **outfiles, int *i)
// {
// 	if ((*curr)->type == OUTPUT)
// 	{
// 		(*curr) = (*curr)->next;
// 		if (!extract_outfiles_helper_1((*curr), outfiles, i))
// 			return (0);
// 	}
// 	if ((*curr)->type == APPEND)
// 	{
// 		(*curr) = (*curr)->next;
// 		if (!extract_outfiles_helper_2((*curr), outfiles, i))
// 			return (0);
// 	}
// 	return (1);
// }

void	extract_outfiles(t_token *token, t_file **outfiles, t_free **ptrs)
{
	t_token	*curr;
	int		i;

	(curr = token, i = 0);
	if (curr && curr->type == PIPE)
		curr = curr->next;
	if (!outfiles_len(curr))
		return ;
	*outfiles = ft_malloc(ptrs, (outfiles_len(curr) + 1) * sizeof(t_file));
	while (curr && curr->type != PIPE)
	{
		if (curr->type == OUTPUT)
			(curr = curr->next, extract_outfiles_helper_1(curr, outfiles, &i, ptrs));
		if (curr->type == APPEND)
			(curr = curr->next, extract_outfiles_helper_2(curr, outfiles, &i, ptrs));
		curr = curr->next;
	}
	(*outfiles)[i].fd = -42;
}

