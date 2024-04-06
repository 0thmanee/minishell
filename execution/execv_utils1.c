/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execv_utils1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboutsli <yboutsli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 22:40:46 by yboutsli          #+#    #+#             */
/*   Updated: 2024/04/06 05:34:11 by yboutsli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	new_execve1(t_cmd *cmd, int type)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd->cmd, 2);
	if (type == 1)
		ft_putstr_fd(": No such file or directory\n", 2);
	else if (type == 0)
		ft_putstr_fd(": command not found\n", 2);
}

int	new_execve(t_cmd *cmd, t_list **list_env, t_free **ptrs)
{
	char	**env_tab;
	char	**args;
	char	**npath;
	char	*cmd_fpath;
	int		type[2];

	type[1] = 0;
	args = execve_argv(cmd, ptrs);
	npath = path(list_env, ptrs);
	cmd_fpath = cmd_path(cmd->cmd, npath, ptrs, &type[0]);
	if (!ft_strcmp("./minishell", cmd->cmd))
		type[1] = 1;
	env_tab = list2tab(*list_env, ptrs, type[1]);
	if (!cmd_fpath)
	{
		new_execve1(cmd, type[0]);
		exit (127);
	}
	if (execve(cmd_fpath, args, env_tab) == -1)
	{
		ft_free_all(ptrs);
		new_perror(cmd->cmd);
		exit (1);
	}
	return (0);
}

char	**path(t_list **envp, t_free **ptrs)
{
	char	**npath;
	t_list	*current;

	current = *envp;
	while (current)
	{
		if (!ft_strcmp(current->var, "PATH"))
		{
			npath = ft_split(current->value, ':', ptrs);
			return (npath);
		}
		current = current->next;
	}
	return (NULL);
}
