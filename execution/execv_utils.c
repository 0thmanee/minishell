/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execv_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboutsli <yboutsli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 16:03:22 by yboutsli          #+#    #+#             */
/*   Updated: 2024/03/27 16:49:34 by yboutsli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*cmd_path(char *cmd, char **npath)
{
	int		i;
	char	*tmp;
	char	*tmp1;

	if (*cmd == '\0')
		return (NULL);
	if (cmd[0] == '/')
		return (cmd);
	i = 0;
	while (npath[i])
	{
		tmp = ft_strjoin_2(npath[i], "/");
		tmp1 = ft_strjoin_2(tmp, cmd);
		free(tmp);
		if (!access(tmp1, F_OK))
			return (tmp1);
		free(tmp1);
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

char	**execve_argv(t_cmd *cmd)
{
	char	**args;
	int		size;
	int		i;

	size = args_size(cmd);
	args = malloc((size + 2) * sizeof(char *));
	if (!args)
		return (NULL);
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
int	new_execve(t_cmd *cmd, t_list **list_env)
{
	char	**env_tab;
	char	**args;
	char	**npath;
	char	*cmd_fpath;

	args = execve_argv(cmd);
	npath = path(list_env);
	cmd_fpath = cmd_path(cmd->cmd, npath);
	env_tab = list2tab(*list_env);
	if (!cmd_fpath)
	{
		printf("command not found: %s\n", cmd->cmd);//write instead
		exit (1);
	}
	if (execve(cmd_fpath, args, env_tab) == -1)
	{
		perror(cmd->cmd);
		exit (1);
	}
	return (0);
}