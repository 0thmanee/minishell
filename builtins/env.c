/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboutsli <yboutsli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 14:36:05 by yboutsli          #+#    #+#             */
/*   Updated: 2024/04/19 21:48:01 by yboutsli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	env_utils(t_list **list_env, t_free **ptrs, char *cmd)
{
	char	*new_var;
	char	*cmd_fpath;
	char	**npath;

	npath = path(list_env, ptrs);
	cmd_fpath = cmd_path(cmd, npath, ptrs, 0);
	if (!cmd_fpath)
		new_var = cmd;
	else
		new_var = cmd_fpath;
	ft_free(npath, ptrs);
	printf("_=%s\n", new_var);
}

int	env(t_list **list_env, t_cmd *cmd, t_free **ptrs)
{
	t_list	*curr;

	env_lc_update(cmd, list_env, ptrs);
	if (!list_env)
		return (1);
	curr = *list_env;
	while (curr)
	{
		if (!ft_strcmp(curr->var, "_"))
			env_utils(list_env, ptrs, cmd->cmd);
		else if (curr->value)
			printf("%s=%s\n", curr->var, curr->value);
		curr = curr->next;
	}
	return (0);
}
