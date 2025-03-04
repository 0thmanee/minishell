/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execv_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboutsli <yboutsli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 16:03:22 by yboutsli          #+#    #+#             */
/*   Updated: 2024/04/20 14:06:06 by yboutsli         ###   ########.fr       */
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
		args[1] = NULL;
	else
	{
		i = 0;
		while (++i <= size + 1)
			args[i] = cmd->args[i - 1];
	}
	return (args);
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

void	cmd_error(char *str1, char *str2)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(str1, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(str2, 2);
	ft_putstr_fd("\n", 2);
}
