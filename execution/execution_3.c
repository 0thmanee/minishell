/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboutsli <yboutsli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 22:50:51 by yboutsli          #+#    #+#             */
/*   Updated: 2024/04/05 22:56:12 by yboutsli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close2(int tab[2])
{
	close(tab[0]);
	close(tab[1]);
}

void	fd2(int tab[2])
{
	dup2(tab[0], 0);
	dup2(tab[1], 1);
	close2(tab);
}

int	*fd1(t_free **ptrs)
{
	int	*tab;

	tab = ft_malloc(ptrs, sizeof(int) * 2);
	tab[0] = dup(0);
	tab[1] = dup(1);
	return (tab);
}

int	new_fork(void)
{
	int	pid;

	pid = fork();
	if (pid < 0)
		(write(2, "minishell: ", 11), perror("Fork"), exit(1));
	return (pid);
}
