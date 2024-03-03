/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboutsli <yboutsli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 12:54:58 by yboutsli          #+#    #+#             */
/*   Updated: 2024/03/02 16:45:11 by yboutsli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*new;

	new = malloc(sizeof(t_list));
	if (!new)
		return (NULL);
	new->content = ft_strdup(content);
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


void	ft_lstadd_back(t_list **lst, t_list *new)
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
		free(p->content);
		free(p);
		p = next;
	}
	*lst = NULL;
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while (s1[i] == s2[i] && s1[i] && s2[i] && i < n - 1)
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

