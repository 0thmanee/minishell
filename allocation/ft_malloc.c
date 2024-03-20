/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouchta <obouchta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 01:46:06 by yboutsli          #+#    #+#             */
/*   Updated: 2024/03/20 22:03:05 by obouchta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_lstadd_back_aloc(t_free **list_aloc, t_free *new)
{
	t_free	*curr;

	if (new == NULL)
		return ;
	if (*list_aloc == NULL)
	{
		*list_aloc = new;
		new->next = NULL;
		return ;
	}
	curr = *list_aloc;
	while (curr && curr->next)
		curr = curr->next;
	curr->next = new;
}

t_free	*ft_lstnew_aloc(void *ptr)
{
	t_free	*new;

	new = malloc(sizeof(t_free));
	if (!new)
		return(NULL);
	new->ptr = ptr;
	return (new);
}

void	*ft_malloc1(t_free **list_aloc, size_t size)
{
	t_free	*new;
	void	*ptr;

	ptr = malloc(size);
	if (!ptr)
		exit (1);
	new = ft_lstnew_aloc1(ptr);
	ft_lstadd_back_aloc(list_aloc, new);
	return (ptr);
}

void	**ft_malloc2(t_free **list_aloc, size_t size)
{
	t_free	*new;
	void	*ptr;

	ptr = malloc(size);
	if (!ptr)
		exit (1);
	new = ft_lstnew_aloc2(ptr);
	ft_lstadd_back_aloc(list_aloc, new);
	return (ptr);
}
void	ft_free_ptr(t_free **list_aloc, void *ptr)
{
	t_free *current;
	t_free *prev;

	current = *list_aloc
	prev = NULL
	while (current)
	{
		if (current->ptr == ptr)
		{
			if (prev)
				prev->next = current->next;
			else
				*list_aloc = current->next;
			
			free(current->ptr);
			free(current);
			return ;
		}
		prev = current;
		current = current->next;
	}
}

void ft_free_all(t_free **list_aloc)
{
	t_free *current = *list_aloc;
	t_free *next;

	while (current)
	{
		next = current->next;
		if (current->ptr1)
			free(current->ptr1);
		else if (current->ptr2)
			free(current->ptr2);
		free(current);
		current = next;
	}
	*list_aloc = NULL;
}
