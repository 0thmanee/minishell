/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execv_utils1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboutsli <yboutsli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 22:40:46 by yboutsli          #+#    #+#             */
/*   Updated: 2024/04/23 14:15:35 by yboutsli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*rm_slash(char *cmd, t_free **ptrs)
{
	int		cmd_len;
	char	*tmp;

	cmd_len = ft_strlen(cmd);
	if (cmd_len != 0 && cmd[cmd_len - 1] == '/')
		tmp = ft_substr(cmd, 0, cmd_len - 1, ptrs);
	else
		tmp = ft_strdup(cmd, ptrs);
	return (tmp);
}

void	check_cmd1(char *cmd, t_free **ptrs, struct stat statbuf)
{
	char	*tmp;

	tmp = rm_slash(cmd, ptrs);
	if (access(tmp, F_OK) == 0 && S_ISREG(statbuf.st_mode) == 0)
	{
		ft_free_ptr(ptrs, tmp);
		cmd_error(cmd, "Not a directory");
		exit(126);
	}
	else
	{
		ft_free_ptr(ptrs, tmp);
		cmd_error(cmd, "No such file or directory");
		exit(127);
	}
}

void	check_cmd(char *cmd, char **cmd_fpath, t_free **ptrs)
{
	struct stat	statbuf;

	stat(cmd, &statbuf);
	if (access(cmd, F_OK) == 0 && stat(cmd, &statbuf) == 0)
	{
		if (S_ISREG(statbuf.st_mode) && statbuf.st_size == 0)
			exit(0);
		if (S_ISREG(statbuf.st_mode))
			*cmd_fpath = ft_strdup(cmd, ptrs);
		else if (S_ISDIR(statbuf.st_mode))
			(cmd_error(cmd, "is a directory"), exit(126));
		else
			(cmd_error(cmd, "command not found"), exit(127));
	}
	else
		check_cmd1(cmd, ptrs, statbuf);
}

int	slash_point(char *cmd)
{
	int	i;

	i = 0;
	if (cmd && cmd[0] == '.')
		return (0);
	while (cmd && cmd[i] != '\0')
	{
		if (cmd[i] == '/')
			return (0);
		i++;
	}
	return (1);
}

int	new_execve(t_cmd *cmd, t_list **list_env, t_free **ptrs)
{
	char	**env_tab;
	char	**args;
	char	**npath;
	char	*cmd_fpath;

	cmd_fpath = NULL;
	npath = path(list_env, ptrs);
	args = execve_argv(cmd, ptrs);
	env_tab = list2tab(*list_env, ptrs);
	if (!slash_point(cmd->cmd))
		check_cmd(cmd->cmd, &cmd_fpath, ptrs);
	else
	{
		if (!npath)
			(cmd_error(cmd->cmd, "No such file or directory"), exit(127));
		cmd_fpath = cmd_path(cmd->cmd, npath, ptrs);
		if (!cmd_fpath)
			(cmd_error(cmd->cmd, "command not found"), exit(127));
	}
	if (execve(cmd_fpath, args, env_tab) == -1)
	{
		new_perror(cmd->cmd);
		(ft_free_all(ptrs), exit (1));
	}
	return (0);
}
