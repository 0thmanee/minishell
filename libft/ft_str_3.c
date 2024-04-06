/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouchta <obouchta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 05:10:23 by obouchta          #+#    #+#             */
/*   Updated: 2024/04/06 05:12:42 by obouchta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_lstsize(t_cmd *lst)
{
	int	count;

	count = 0;
	if (lst == NULL)
		return (0);
	while (lst)
	{
		lst = lst->next;
		count++;
	}
	return (count);
}

char	*ft_strjoin_2(char *s1, char *s2)
{
	size_t	len_s1;
	size_t	len_s2;
	char	*p;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	p = (char *)malloc (sizeof(char) * (len_s1 + len_s2 + 1));
	if (!p)
		return (NULL);
	while (i < len_s1 && s1[i])
	{
		p[i] = s1[i];
		i++;
	}
	while (j < len_s2 && s2[j])
	{
		p[i + j] = s2[j];
		j++;
	}
	p[j + i] = '\0';
	return (p);
}

int	is_ambig(char *value)
{
	int	i;

	if (!value || !value[0])
		return (1);
	i = 0;
	while (value[i] && is_whitespace(value[i]))
		i++;
	if (!value[i])
		return (1);
	while (value[i])
	{
		if (is_whitespace(value[i]))
			break ;
		i++;
	}
	while (value[i] && is_whitespace(value[i]))
		i++;
	if (value[i])
		return (1);
	return (0);
}

void	ft_putstr_fd(char *s, int fd)
{
	int		i;
	char	c;

	i = 0;
	if (!s)
		return ;
	while (s[i])
	{
		c = s[i];
		write(fd, &c, 1);
		i++;
	}
}
