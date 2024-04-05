/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execv_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboutsli <yboutsli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 16:03:22 by yboutsli          #+#    #+#             */
/*   Updated: 2024/04/05 22:41:54 by yboutsli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*shear_in_cwd(char *cmd, t_free **ptrs, int *type)
{
	char	*tmp[3];
	char	*pwd;

	tmp[0] = ft_substr(cmd, 2, ft_strlen(cmd), ptrs);
	tmp[2] = ft_strjoin("/", tmp[0], ptrs);
	ft_free_ptr(ptrs, tmp[0]);
	pwd = getcwd(NULL, 0);
	if (!pwd)
		return (NULL);
	tmp[1] = ft_strjoin(pwd, tmp[2], ptrs);
	if (!access(tmp[1], F_OK))
	{
		free(pwd);
		ft_free_ptr(ptrs, tmp[2]);
		return (tmp[1]);
	}
	else
	{
		ft_free_ptr(ptrs, tmp[1]);
		ft_free_ptr(ptrs, tmp[2]);
		if (type != 0)
			*type = 1;
		return (NULL);
	}
}

char	*cmd_path(char *cmd, char **npath, t_free **ptrs, int *type)
{
	int		i;
	char	*tmp;
	char	*tmp1;

	if (!cmd || *cmd == '\0' || !npath)
		return (NULL);
	if (cmd[0] == '/')
		return (cmd);
	else if (!ft_strncmp(cmd, "./", 2))
		return (shear_in_cwd(cmd, ptrs, type));
	i = 0;
	while (npath && npath[i])
	{
		tmp = ft_strjoin(npath[i], "/", ptrs);
		tmp1 = ft_strjoin(tmp, cmd, ptrs);
		ft_free_ptr(ptrs, tmp);
		if (!access(tmp1, F_OK & X_OK))
			return (tmp1);
		ft_free_ptr(ptrs, tmp1);
		i++;
	}
	if (type != 0)
		*type = 0;
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
		args[1] = NULL;
	else
	{
		i = 0;
		while (++i <= size + 1)
			args[i] = cmd->args[i - 1];
	}
	return (args);
}
