/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboutsli <yboutsli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 13:59:00 by yboutsli          #+#    #+#             */
/*   Updated: 2024/04/05 14:53:37 by yboutsli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pwd(t_list **list_env)
{
	char	*cwd;

	cwd = get_env(list_env, "PWD");
	if (!cwd)
	{
		cwd = getcwd(NULL, 0);
		if (cwd)
		{
			printf("%s\n", cwd);
			free(cwd);
			return (0);
		}
	}
	printf("%s\n", cwd);
	return (0);
}
