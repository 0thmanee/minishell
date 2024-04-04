/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execv_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouchta <obouchta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 16:03:22 by yboutsli          #+#    #+#             */
/*   Updated: 2024/04/04 01:49:00 by obouchta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*cmd_path(char *cmd, char **npath, t_free **ptrs)
{
	int		i;
	char	*tmp;
	char	*tmp1;

	if (!cmd || *cmd == '\0')
		return (NULL);
	if (cmd[0] == '/')
		return (cmd);
	i = 0;
	while (npath && npath[i])
	{
		tmp = ft_strjoin(npath[i], "/", ptrs);
		tmp1 = ft_strjoin(tmp, cmd, ptrs);
		ft_free_ptr(ptrs, tmp);
		if (!access(tmp1, F_OK | X_OK))
			return (tmp1);
		ft_free_ptr(ptrs, tmp1);
		i++;
	}
	return (NULL);
}
int	args_size(t_cmd *cmd)
{
	int	i;

	if (cmd->args == NULL)
		return (0);
	i = 0;
	while (cmd->args[i])
		i++;
	return (i);
}

char	**execve_argv(t_cmd *cmd, t_free **ptrs)
{
	char	**args;
	int		size;
	int		i;

	size = args_size(cmd);
	args = ft_malloc(ptrs, (size + 2) * sizeof(char *));
	args[0] = cmd->cmd;
	if (size == 0)
		args[1] =  NULL;
	else
	{
		i = 0;
		while (++i <= size + 1)
			args[i] = cmd->args[i - 1];
	}
	return (args);
}
int	new_execve(t_cmd *cmd, t_list **list_env, t_free **ptrs)
{
	char	**env_tab;
	char	**args;
	char	**npath;
	char	*cmd_fpath;

	args = execve_argv(cmd, ptrs);
	npath = path(list_env, ptrs);
	cmd_fpath = cmd_path(cmd->cmd, npath, ptrs);
	env_tab = list2tab(*list_env, ptrs);
	if (!cmd_fpath)
	{
		printf("command not found: %s\n", cmd->cmd);
		exit (127);
	}
	if (execve(cmd_fpath, args, env_tab) == -1)
	{
		perror(cmd->cmd);
		exit (1);
	}
	return (0);
}