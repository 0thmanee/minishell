/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   final_cmd_3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboutsli <yboutsli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 05:23:00 by obouchta          #+#    #+#             */
/*   Updated: 2024/04/26 15:48:25 by yboutsli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	extract_files_helper_1(t_token *curr, t_file *files,
	t_new_3 *new_strct)
{
	files[new_strct->i].no_quote = curr->no_quote;
	files[new_strct->i].is_var = curr->vars_len;
	if (!curr->value && curr->vars_len && !(curr->no_quote))
		files[new_strct->i].file = ft_strdup("", new_strct->ptrs);
	else
		files[new_strct->i].file = ft_strdup(curr->value, new_strct->ptrs);
	files[new_strct->i].fd = -1;
	files[new_strct->i].type = 0;
	(new_strct->i)++;
}

int	extract_files_helper_2(t_token *curr, t_file *files,
	t_new_3 *new_strct)
{
	files[new_strct->i].no_quote = curr->no_quote;
	files[new_strct->i].is_var = curr->vars_len;
	files[new_strct->i].file = generate_file_name(new_strct->ptrs);
	files[new_strct->i].type = 1;
	files[new_strct->i].delimiter = ft_strdup(curr->value, new_strct->ptrs);
	if (here_doc(files + new_strct->i, new_strct->list_env, new_strct->ptrs))
		return (1);
	(new_strct->i)++;
	return (0);
}

void	extract_files_helper_3(t_token *curr, t_file *files,
	t_new_3 *new_strct)
{
	files[new_strct->i].no_quote = curr->no_quote;
	files[new_strct->i].is_var = curr->vars_len;
	if (!curr->value && curr->vars_len && !(curr->no_quote))
		files[new_strct->i].file = ft_strdup("", new_strct->ptrs);
	else
		files[new_strct->i].file = ft_strdup(curr->value, new_strct->ptrs);
	files[new_strct->i].fd = -1;
	files[new_strct->i].type = 2;
	(new_strct->i)++;
}

void	extract_files_helper_4(t_token *curr, t_file *files,
	t_new_3 *new_strct)
{
	files[new_strct->i].no_quote = curr->no_quote;
	files[new_strct->i].is_var = curr->vars_len;
	if ((!curr->value) && curr->vars_len && !(curr->no_quote))
		files[new_strct->i].file = ft_strdup("", new_strct->ptrs);
	else
		files[new_strct->i].file = ft_strdup(curr->value, new_strct->ptrs);
	files[new_strct->i].fd = -1;
	files[new_strct->i].type = 3;
	(new_strct->i)++;
}
