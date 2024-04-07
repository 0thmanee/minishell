/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   final_cmd_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouchta <obouchta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 05:22:00 by obouchta          #+#    #+#             */
/*   Updated: 2024/04/06 22:11:39 by obouchta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	infiles_len(t_token *curr)
{
	int	len;

	len = 0;
	while (curr && curr->type != PIPE)
	{
		if (curr->type == IN_FILE || curr->type == HERE_DOC)
			len++;
		curr = curr->next;
	}
	return (len);
}

void	extract_infiles_helper_1(t_token *curr, t_file *infiles,
	int *i, t_free **ptrs)
{
	infiles[*i].file = ft_strdup(curr->value, ptrs);
	infiles[*i].fd = -1;
	infiles[*i].type = 0;
	infiles[*i].delim_flag = 0;
	infiles[*i].is_var = curr->vars_len;
	(*i)++;
}

void	extract_infiles_helper_2(t_token *curr, t_file *infiles,
	int *i, t_free **ptrs)
{
	infiles[*i].file = NULL;
	infiles[*i].fd = -1;
	infiles[*i].type = 1;
	infiles[*i].delimiter = ft_strdup(curr->value, ptrs);
	infiles[*i].delim_flag = curr->delim_flag;
	infiles[*i].is_var = curr->vars_len;
	(*i)++;
}

void	extract_infiles(t_token *token, t_cmd *cmd, t_free **ptrs)
{
	t_token	*curr;
	int		i;

	curr = token;
	i = 0;
	if (curr && curr->type == PIPE)
		curr = curr->next;
	if (!infiles_len(curr))
		return ;
	cmd->infiles = ft_malloc(ptrs, (infiles_len(curr) + 1) * sizeof(t_file));
	while (curr && curr->type != PIPE)
	{
		if (curr->type == IN_FILE)
			extract_infiles_helper_1(curr, cmd->infiles, &i, ptrs);
		if (curr->type == DELIMITER)
			extract_infiles_helper_2(curr, cmd->infiles, &i, ptrs);
		curr = curr->next;
	}
	cmd->infiles[i].fd = -42;
}
