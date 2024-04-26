/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   final_cmd_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouchta <obouchta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 05:22:00 by obouchta          #+#    #+#             */
/*   Updated: 2024/04/26 15:36:03 by obouchta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	files_len(t_token *curr)
{
	int	len;

	len = 0;
	while (curr && curr->type != PIPE)
	{
		if (curr->type == IN_FILE || curr->type == HERE_DOC
			|| curr->type == OUT_FILE)
			len++;
		curr = curr->next;
	}
	return (len);
}

void	set_last_i_o(t_cmd *cmd, int count, int i)
{
	if (count - 1 == i)
		cmd->files[i].last_in_out = 1;
	else
		cmd->files[i].last_in_out = 0;
}

void	check_last_in_out(t_cmd *cmd, t_token *curr, int i, int i_o)
{
	int		in;
	int		out;
	int		j;

	j = 0;
	while (curr && curr->type != PIPE)
	{
		if (curr->type == IN_FILE || curr->type == DELIMITER)
		{
			j++;
			in = j;
		}
		if (curr->type == OUTPUT || curr->type == APPEND)
		{
			j++;
			out = j;
		}
		curr = curr->next;
	}
	if (i_o == 1)
		set_last_i_o(cmd, in, i);
	if (i_o == 2)
		set_last_i_o(cmd, out, i);
}

int	extract_files_check(t_token *curr, t_cmd *cmd, t_new_3 *new_strct)
{
	if (curr->type == IN_FILE)
		extract_files_helper_1(curr, cmd->files, new_strct);
	if (curr->type == DELIMITER)
		if (extract_files_helper_2(curr, cmd->files, new_strct))
			return (1);
	if (curr->type == OUTPUT)
	{
		curr = curr->next;
		extract_files_helper_3(curr, cmd->files, new_strct);
	}
	if (curr->type == APPEND)
	{
		curr = curr->next;
		extract_files_helper_4(curr, cmd->files, new_strct);
	}
	return (0);
}

int	extract_files(t_token *token, t_cmd *cmd, t_list *list_env, t_free **ptrs)
{
	t_token	*curr;
	t_token	*first;
	t_new_3	new_strct;

	(1) && (curr = token, new_strct.i = 0);
	(1) && (new_strct.list_env = list_env, new_strct.ptrs = ptrs);
	if (curr && curr->type == PIPE)
		curr = curr->next;
	first = curr;
	if (!files_len(curr))
		return (0);
	cmd->files = ft_malloc(new_strct.ptrs,
			(files_len(curr) + 1) * sizeof(t_file));
	while (curr && curr->type != PIPE)
	{
		if (curr->type == IN_FILE || curr->type == DELIMITER)
			check_last_in_out(cmd, first, new_strct.i, 1);
		if (curr->type == OUTPUT || curr->type == APPEND)
			check_last_in_out(cmd, first, new_strct.i, 2);
		if (extract_files_check(curr, cmd, &new_strct))
			return (1);
		curr = curr->next;
	}
	cmd->files[new_strct.i].fd = -42;
	return (0);
}
