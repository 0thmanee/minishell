/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouchta <obouchta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 22:51:37 by obouchta          #+#    #+#             */
/*   Updated: 2024/03/17 21:33:47 by obouchta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


t_cmd	*ft_lstnew_3(char *cmd, char **args, t_file *infiles, t_file *outfiles)
{
	t_cmd	*new_node;

	new_node = (t_cmd *)malloc(sizeof(t_cmd));
	if (!new_node)
		return (NULL);
	new_node->cmd = cmd;
	new_node->args = args;
	new_node->infiles = infiles;
	new_node->outfiles = outfiles;
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