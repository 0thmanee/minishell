/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouchta <obouchta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 05:10:23 by obouchta          #+#    #+#             */
/*   Updated: 2024/04/25 03:58:07 by obouchta         ###   ########.fr       */
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

int	is_ambig(t_file io_file)
{
	int	i;

	if (io_file.file && !io_file.file[0])
		return (0);
	if (!io_file.file)
		return (1);
	i = 0;
	while (io_file.file[i] && is_whitespace(io_file.file[i]))
		i++;
	if (!io_file.file[i])
		return (1);
	while (io_file.file[i])
	{
		if (is_whitespace(io_file.file[i]))
			break ;
		i++;
	}
	while (io_file.file[i] && is_whitespace(io_file.file[i]))
		i++;
	if (io_file.file[i])
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
