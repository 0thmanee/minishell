/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   final_cmd_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouchta <obouchta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 05:22:00 by obouchta          #+#    #+#             */
/*   Updated: 2024/03/18 22:55:40 by obouchta         ###   ########.fr       */
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

int	extract_infiles_helper_1(t_token *curr, t_file **infiles, int *i)
{
	(*infiles)[*i].fd = open(curr->value, O_RDWR);
	if ((*infiles)[*i].fd == -1)
		perror("minishell");
	(*infiles)[*i].type = 0;
	(*i)++;
	return (1);
}

int	extract_infiles_helper_2(t_token *curr, t_file **infiles, int *i)
{
	(*infiles)[*i].fd = -2;
	(*infiles)[*i].type = 1;
	(*infiles)[*i].delimiter = strdup(curr->value);
	if (!(*infiles)[*i].delimiter)
		return (0);
	(*i)++;
	return (1);
}

int	extract_infiles(t_token *token, t_file **infiles)
{
	t_token	*curr;
	int		i;

	curr = token;
	i = 0;
	if (curr && curr->type == PIPE)
		curr = curr->next;
	if (!infiles_len(curr))
		return (1);
	*infiles = malloc((infiles_len(curr) + 1) * sizeof(t_file));
	if (!(*infiles))
		return (0);
	while (curr && curr->type != PIPE)
	{
		if (curr->type == IN_FILE
			&& !extract_infiles_helper_1(curr, infiles, &i))
			return (0);
		if (curr->type == DELIMITER
			&& !extract_infiles_helper_2(curr, infiles, &i))
			return (0);
		curr = curr->next;
	}
	(*infiles)[i].fd = -42;
	return (1);
}
