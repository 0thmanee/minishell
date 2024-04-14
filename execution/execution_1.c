/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouchta <obouchta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 03:41:21 by yasser03          #+#    #+#             */
/*   Updated: 2024/04/14 15:55:15 by obouchta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*int_to_str(int num, t_free **ptrs)
{
	int		len;
	int		tmp;
	char	*str;

	len = 1;
	tmp = num;
	while (tmp != 0)
	{
		tmp /= 10;
		len++;
	}
	if (num == 0)
		len = 2;
	str = ft_malloc(ptrs, len + 1);
	str[--len] = '\0';
	while (len)
	{
		str[--len] = (num % 10) + '0';
		num /= 10;
	}
	return (str);
}

int	env_size(t_list *list_env)
{
	int		count;
	t_list	*current;

	count = 0;
	current = list_env;
	while (current)
	{
		if (current->var && current->value)
			count++;
		current = current->next;
	}
	return (count);
}

int	ft_execution(t_cmd **cmd, t_list **list_env, t_free **ptrs)
{
	int	status;
	int	*fd;

	fd = fd1(ptrs);
	status = 0;
	if (ft_lstsize(*cmd) == 1)
		status = execute_1(*cmd, list_env, ptrs, fd);
	else
		status = execute_2(cmd, list_env, ptrs, fd);
	exit_status(0, status);
	fd2(fd);
	ft_free_ptr(ptrs, fd);
	return (status);
}
