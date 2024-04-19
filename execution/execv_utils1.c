/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execv_utils1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouchta <obouchta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 22:40:46 by yboutsli          #+#    #+#             */
/*   Updated: 2024/04/19 19:44:00 by obouchta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_check(char *cmd, t_free **ptrs)
{
	struct stat	file_stat;

	if (access(cmd, F_OK | X_OK) == 0)
	{
		if (stat(cmd, &file_stat) == 0 && S_ISDIR(file_stat.st_mode))
		{
			ft_putstr_fd("minishell: ", 2);
			(ft_putstr_fd(cmd, 2), ft_putstr_fd(": is a directory\n", 2));
			(ft_free_all(ptrs), exit(126));
		}
	}
}

static void	new_execve1(t_cmd *cmd, char **args, char **env_tab, int type)
{
	if (execve(cmd->cmd, args, env_tab) == 0)
		exit(0);
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd->cmd, 2);
	if (type == 1)
		ft_putstr_fd(": No such file or directory\n", 2);
	else
		ft_putstr_fd(": command not found\n", 2);
	exit(127);
}

int	new_execve(t_cmd *cmd, t_list **list_env, t_free **ptrs)
{
	char	**env_tab;
	char	**args;
	char	**npath;
	char	*cmd_fpath;
	int		type;

	type = 0;
	args = execve_argv(cmd, ptrs);
	npath = path(list_env, ptrs);
	cmd_fpath = cmd_path(cmd->cmd, npath, ptrs, &type);
	env_tab = list2tab(*list_env, ptrs);
	if (!cmd_fpath)
		new_execve1(cmd, args, env_tab, type);
	if (execve(cmd_fpath, args, env_tab) == -1)
	{
		ft_check(cmd->cmd, ptrs);
		new_perror(cmd->cmd);
		if (access(cmd->cmd, F_OK | X_OK) == -1)
			(ft_free_all(ptrs), exit (127));
		(ft_free_all(ptrs), exit (1));
	}
	return (0);
}

char	**path(t_list **envp, t_free **ptrs)
{
	char	**npath;
	t_list	*current;

	current = *envp;
	if (!envp)
		return (NULL);
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
