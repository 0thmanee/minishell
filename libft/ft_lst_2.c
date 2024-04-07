/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouchta <obouchta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 22:51:37 by obouchta          #+#    #+#             */
/*   Updated: 2024/04/06 22:32:58 by obouchta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*ft_lstnew_3(t_free **ptrs)
{
	t_cmd	*new_node;

	new_node = ft_malloc(ptrs, sizeof(t_cmd));
	new_node->cmd = NULL;
	new_node->args = NULL;
	new_node->infiles = NULL;
	new_node->outfiles = NULL;
	new_node->io_error = 0;
	new_node->cmd_is_var = 0;
	new_node->next = NULL;
	return (new_node);
}

void	ft_lstadd_back_3(t_cmd **lst, t_cmd *new_node)
{
	t_cmd	*curr;

	if (new_node == NULL)
		return ;
	if (*lst == NULL)
	{
		*lst = new_node;
		new_node->next = NULL;
		return ;
	}
	curr = *lst;
	while (curr && curr->next)
		curr = curr->next;
	curr->next = new_node;
}
