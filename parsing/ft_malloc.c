/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboutsli <yboutsli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 01:46:06 by yboutsli          #+#    #+#             */
/*   Updated: 2024/04/18 20:55:37 by yboutsli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_lstadd_back_aloc(t_free **list_aloc, t_free *new)
{
	t_free	*curr;

	if (new == NULL)
		return ;
	if (!(*list_aloc))
	{
		*list_aloc = new;
		return ;
	}
	curr = *list_aloc;
	while (curr && curr->next)
		curr = curr->next;
	curr->next = new;
}

t_free	*ft_lstnew_aloc(void *ptr, t_free **list_aloc)
{
	t_free	*new;

	new = malloc(sizeof(t_free));
	if (!new)
		(ft_free_all(list_aloc), exit(1));
	new->ptr = ptr;
	new->next = NULL;
	return (new);
}

void	*ft_malloc(t_free **list_aloc, size_t size)
{
	t_free	*new_node;
	void	*ptr;

	ptr = malloc(size);
	if (!ptr)
		(ft_free_all(list_aloc), exit(1));
	new_node = ft_lstnew_aloc(ptr, list_aloc);
	ft_lstadd_back_aloc(list_aloc, new_node);
	return (ptr);
}

void	ft_free_ptr(t_free **list_aloc, void *ptr)
{
	t_free	*current;
	t_free	*prev;

	current = *list_aloc;
	prev = NULL;
	if (!ptr)
		return ;
	while (current)
	{
		if (current->ptr == ptr)
		{
			if (prev)
				prev->next = current->next;
			else
				*list_aloc = current->next;
			free(current->ptr);
			current->ptr = NULL;
			free(current);
			current = NULL;
			return ;
		}
		prev = current;
		current = current->next;
	}
}

void	ft_free_all(t_free **list_aloc)
{
	t_free	*current;
	t_free	*next;

	current = *list_aloc;
	while (current)
	{
		next = current->next;
		free(current->ptr);
		current->ptr = NULL;
		free(current);
		current = next;
	}
	*list_aloc = NULL;
}
