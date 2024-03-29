/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   final_cmd_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouchta <obouchta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 05:22:00 by obouchta          #+#    #+#             */
/*   Updated: 2024/03/29 03:52:54 by obouchta         ###   ########.fr       */
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

void	extract_infiles_helper_1(t_token *curr, t_file **infiles, int *i)
{
	(*infiles)[*i].fd = open(curr->value, O_RDWR);
	(*infiles)[*i].type = 0;
	(*infiles)[*i].delim_flag = 0;
	(*i)++;
}

void	extract_infiles_helper_2(t_token *curr, t_file **infiles, int *i, t_free **ptrs)
{
	(*infiles)[*i].fd = -2;
	(*infiles)[*i].type = 1;
	(*infiles)[*i].delimiter = ft_strdup(curr->value, ptrs);
	if (curr->delim_flag)
		(*infiles)[*i].delim_flag = 1;
	else
		(*infiles)[*i].delim_flag = 0;
	(*i)++;
}

void	extract_infiles(t_token *token, t_file **infiles, t_free **ptrs)
{
	t_token	*curr;
	int		i;

	curr = token;
	i = 0;
	if (curr && curr->type == PIPE)
		curr = curr->next;
	if (!infiles_len(curr))
		return ;
	*infiles = ft_malloc(ptrs, (infiles_len(curr) + 1) * sizeof(t_file));
	if (!(*infiles))
		(ft_free_all(ptrs), exit(1));
	while (curr && curr->type != PIPE)
	{
		if (curr->type == IN_FILE)
			extract_infiles_helper_1(curr, infiles, &i);
		if (curr->type == DELIMITER)
			extract_infiles_helper_2(curr, infiles, &i, ptrs);
		curr = curr->next;
	}
	(*infiles)[i].fd = -42;
}
