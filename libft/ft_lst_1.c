/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouchta <obouchta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 21:41:01 by obouchta          #+#    #+#             */
/*   Updated: 2024/03/12 04:57:50 by obouchta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*ft_lstnew_1(char *value, int type, char **args)
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

void	ft_lstadd_back_1(t_token **lst, t_token *new_node)
{
	t_token	*curr;

	if (new_node == NULL)
		return ;
	new_node->var = 0;
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

t_list	*ft_lstnew_2(void *content1, void *content2)
{
	t_list	*new_node;

	new_node = malloc(sizeof(t_list));
	if (!new_node)
		return (NULL);
	new_node->var = ft_strdup(content1);
	new_node->value = ft_strdup(content2);
	new_node->next = NULL;
	return (new_node);
}

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*p;

	if (!lst)
		return (NULL);
	p = lst;
	while (p -> next)
		p = p -> next;
	return (p);
}

void	ft_lstadd_back_2(t_list **lst, t_list *new_node)
{
	t_list	*p;

	p = NULL;
	if (!lst || !new_node)
		return ;
	if (! *lst)
		*lst = new_node;
	else
	{
		p = ft_lstlast(*lst);
		p -> next = new_node;
	}
}

