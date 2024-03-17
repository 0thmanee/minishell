/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouchta <obouchta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 19:09:27 by obouchta          #+#    #+#             */
/*   Updated: 2024/03/07 20:26:02 by obouchta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_lstfree(t_list **lst)
{
	t_list	*p;
	t_list	*next;

	if (!lst)
		return ;
	p = *lst;
	while (p)
	{
		next = p -> next;
		free(p->var);
		free(p->value);
		free(p);
		p = next;
	}
	*lst = NULL;
}

int	free_spesific(t_free **lst, void *ptr)
{
	t_free	*p;
	t_free	*prev;

	if (!lst)
		return (0);
	p = *lst;
	prev = NULL;
	while (p)
	{
		if (p->ptr == ptr)
		{
			if (prev)
				prev->next = p->next;
			else
				*lst = p->next;
			free(p->ptr);
			free(p);
			return (1);
		}
		prev = p;
		p = p->next;
	}
	return (0);
}

void	ft_free_ptrs(t_free **lst, void *ptr)
{
	t_free	*p;

	if (!lst)
		return ;
	p = *lst;
	if (free_spesific(lst, ptr))
		return ;
	if (ptr == NULL)
	{
		p = *lst;
		while (p)
		{
			t_free *next = p->next;
			free(p->ptr);
			free(p);
			p = next;
		}
		*lst = NULL;
	}
}
