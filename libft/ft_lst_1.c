/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouchta <obouchta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 21:41:01 by obouchta          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/03/15 23:58:54 by obouchta         ###   ########.fr       */
=======
/*   Updated: 2024/03/17 05:48:48 by obouchta         ###   ########.fr       */
>>>>>>> Othmane
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*ft_lstnew_1(char *value, int type, t_value *args)
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
	t_list	*new;

	new = malloc(sizeof(t_list));
	if (!new)
		return (NULL);
	new->var = ft_strdup(content1);
	new->value = ft_strdup(content2);
	new->next = NULL;
	return (new);
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

void	ft_lstadd_back_2(t_list **lst, t_list *new)
{
	t_list	*p;

	p = NULL;
	if (!lst || !new)
		return ;
	if (! *lst)
		*lst = new;
	else
	{
		p = ft_lstlast(*lst);
		p -> next = new;
	}
}

