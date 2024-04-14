/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouchta <obouchta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 13:59:00 by yboutsli          #+#    #+#             */
/*   Updated: 2024/04/14 15:46:53 by obouchta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pwd(t_list **list_env, t_free **ptrs)
{
	char	*cwd;

	cwd = get_env(list_env, "PWD", 0, ptrs);
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
