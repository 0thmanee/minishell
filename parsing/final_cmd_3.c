/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   final_cmd_3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouchta <obouchta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 05:23:00 by obouchta          #+#    #+#             */
/*   Updated: 2024/04/06 22:11:57 by obouchta         ###   ########.fr       */
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

int	extract_outfiles_helper_1(t_token *curr, t_file *outfiles,
	int *i, t_free **ptrs)
{
	outfiles[*i].file = ft_strdup(curr->value, ptrs);
	outfiles[*i].fd = -1;
	outfiles[*i].type = 2;
	outfiles[*i].delim_flag = 0;
	outfiles[*i].is_var = curr->vars_len;
	(*i)++;
	return (1);
}

int	extract_outfiles_helper_2(t_token *curr, t_file *outfiles,
	int *i, t_free **ptrs)
{
	outfiles[*i].file = ft_strdup(curr->value, ptrs);
	outfiles[*i].fd = -1;
	outfiles[*i].type = 3;
	outfiles[*i].delim_flag = 0;
	outfiles[*i].is_var = curr->vars_len;
	(*i)++;
	return (1);
}

void	extract_outfiles(t_token *token, t_cmd *cmd, t_free **ptrs)
{
	t_token	*curr;
	int		i;

	curr = token;
	i = 0;
	if (curr && curr->type == PIPE)
		curr = curr->next;
	if (!outfiles_len(curr))
		return ;
	cmd->outfiles = ft_malloc(ptrs, (outfiles_len(curr) + 1) * sizeof(t_file));
	while (curr && curr->type != PIPE)
	{
		if (curr->type == OUTPUT)
		{
			curr = curr->next;
			extract_outfiles_helper_1(curr, cmd->outfiles, &i, ptrs);
		}
		if (curr->type == APPEND)
		{
			curr = curr->next;
			extract_outfiles_helper_2(curr, cmd->outfiles, &i, ptrs);
		}
		curr = curr->next;
	}
	cmd->outfiles[i].fd = -42;
}
