/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execv_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboutsli <yboutsli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 16:03:22 by yboutsli          #+#    #+#             */
/*   Updated: 2024/03/24 22:50:58 by yboutsli         ###   ########.fr       */
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


