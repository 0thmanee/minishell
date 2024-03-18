/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   final_cmd_3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouchta <obouchta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 05:23:00 by obouchta          #+#    #+#             */
/*   Updated: 2024/03/18 03:13:02 by obouchta         ###   ########.fr       */
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

int	extract_outfiles_helper_1(t_token *curr, t_file **outfiles, int *i)
{
	(*outfiles)[*i].fd = open(curr->value, O_CREAT | O_RDWR, 0644);
	if ((*outfiles)[*i].fd == -1) {
		perror("minishell");
		return (0);
	}
	(*outfiles)[*i].type = 2;
	(*i)++;
	return (1);
}

int	extract_outfiles_helper_2(t_token *curr, t_file **outfiles, int *i)
{
	(*outfiles)[*i].fd = open(curr->value, O_CREAT | O_APPEND, 0644);
	if ((*outfiles)[*i].fd == -1)
		perror("minishell");
	(*outfiles)[*i].type = 3;
	(*i)++;
	return (1);
}

int	extract_outfiles(t_token *token, t_file **outfiles)
{
	t_token	*curr;
	int		i;

	curr = token;
	i = 0;
	if (!outfiles_len(curr))
		return (1);
	*outfiles = malloc((outfiles_len(curr) + 1) * sizeof(t_file));
	if (!(*outfiles))
		return (0);
	while (curr && curr->type != PIPE)
	{
		if (curr->type == OUTPUT)
		{
			curr = curr->next;
			if (!extract_outfiles_helper_1(curr, outfiles, &i))
				return (0);
		}
		if (curr->type == APPEND)
		{
			curr = curr->next;
			if (!extract_outfiles_helper_2(curr, outfiles, &i))
				return (0);
		}
		curr = curr->next;
	}
	(*outfiles)[i].fd = -42;
	return (1);
}
