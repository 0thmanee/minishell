/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouchta <obouchta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 13:59:00 by yboutsli          #+#    #+#             */
/*   Updated: 2024/04/04 02:22:17 by obouchta         ###   ########.fr       */
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
		printf("%s\n", cwd);
		return (0); // wtf
	}
	printf("%s\n", cwd);
	return (0);
}
