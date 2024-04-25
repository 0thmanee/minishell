/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   final_cmd_3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouchta <obouchta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 05:23:00 by obouchta          #+#    #+#             */
/*   Updated: 2024/04/25 04:58:34 by obouchta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	extract_files_helper_1(t_token *curr, t_file *files,
	int *i, t_free **ptrs)
{
	files[*i].no_quote = curr->no_quote;
	files[*i].is_var = curr->vars_len;
	if (!curr->value && curr->vars_len && !(curr->no_quote))
		files[*i].file = ft_strdup("", ptrs);
	else
		files[*i].file = ft_strdup(curr->value, ptrs);
	files[*i].fd = -1;
	files[*i].type = 0;
	(*i)++;
}

void	extract_files_helper_2(t_token *curr, t_file *files,
	int *i, t_free **ptrs)
{
	files[*i].no_quote = curr->no_quote;
	files[*i].is_var = curr->vars_len;
	files[*i].file = NULL;
	files[*i].fd = -1;
	files[*i].type = 1;
	files[*i].delimiter = ft_strdup(curr->value, ptrs);
	(*i)++;
}

void	extract_files_helper_3(t_token *curr, t_file *files,
	int *i, t_free **ptrs)
{
	files[*i].no_quote = curr->no_quote;
	files[*i].is_var = curr->vars_len;
	if (!curr->value && curr->vars_len && !(curr->no_quote))
		files[*i].file = ft_strdup("", ptrs);
	else
		files[*i].file = ft_strdup(curr->value, ptrs);
	files[*i].fd = -1;
	files[*i].type = 2;
	(*i)++;
}

void	extract_files_helper_4(t_token *curr, t_file *files,
	int *i, t_free **ptrs)
{
	files[*i].no_quote = curr->no_quote;
	files[*i].is_var = curr->vars_len;
	if ((!curr->value) && curr->vars_len && !(curr->no_quote))
		files[*i].file = ft_strdup("", ptrs);
	else
		files[*i].file = ft_strdup(curr->value, ptrs);
	files[*i].fd = -1;
	files[*i].type = 3;
	(*i)++;
}
