/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functs_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouchta <obouchta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 21:41:01 by obouchta          #+#    #+#             */
/*   Updated: 2024/03/05 04:26:23 by obouchta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_token	*ft_lstnew(char *value, int type, char **args)
{
	t_token	*new_node;

	new_node = (t_token *)malloc(sizeof(t_token));
	if (!new_node)
		return (NULL);
	new_node->value = value;
	new_node->args = args;
	new_node->type = type;
	new_node->next = NULL;
	return (new_node);
}

void	ft_lstadd_back(t_token **lst, t_token *new)
{
	t_token	*curr;

	if (new == NULL)
		return ;
	if (*lst == NULL)
	{
		*lst = new;
		new->next = NULL;
		return ;
	}
	curr = *lst;
	while (curr && curr->next)
		curr = curr->next;
	curr->next = new;
}