/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboutsli <yboutsli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 01:46:06 by yboutsli          #+#    #+#             */
/*   Updated: 2024/03/16 02:26:37 by yboutsli         ###   ########.fr       */
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

t_free	*ft_lstnew_aloc1(void *ptr)
{
	t_free	*new;

	new = malloc(sizeof(t_free));
	if (!new)
		return(NULL);
	new->ptr1 = ptr;
	new->ptr2 = NULL;
	new->next = NULL;
	return (new);
}

void	*ft_malloc1(t_free **list_aloc, int	size)
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

t_free	*ft_lstnew_aloc2(void **ptr)
{
	t_free	*new;

	new = malloc(sizeof(t_free));
	if (!new)
		return(NULL);
	new->ptr1 = NULL;
	new->ptr2 = ptr;
	new->next = NULL;
	return (new);
}

void	**ft_malloc2(t_free **list_aloc, int	size)
{
	t_free	*new;
	void	**ptr;

	ptr = malloc(size);
	if (!ptr)
		exit (1);
	new = ft_lstnew_aloc2(ptr);
	ft_lstadd_back_aloc(list_aloc, new);
	return (ptr);
}
void	ft_free_ptr1(t_free **list_aloc, void *ptr)
{
	t_free	*current;

	current = *list_aloc;
	while (current)
	{
		if (current->ptr1 == ptr)
		{
			free(current->ptr1);
			return ;
		}
		current = current->next;
	}
}