/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   final_cmd_4.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouchta <obouchta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 20:24:01 by obouchta          #+#    #+#             */
/*   Updated: 2024/04/07 00:23:41 by obouchta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	new_args_len(char **old_args, char **splited)
{
	int	len;
	int	i;

	len = 0;
	i = 1;
	if (old_args)
	{
		while (old_args[len])
			len++;
	}
	while (splited[i])
	{
		len++;
		i++;
	}
	return (len);
}

char	**get_splited_args(char **old_args, char **splited, t_free **ptrs)
{
	char	**new_args;
	int		i;
	int		j;

	if (!new_args_len(old_args, splited))
		return (NULL);
	new_args = ft_malloc(ptrs,
			(new_args_len(old_args, splited) + 1) * sizeof(char *));
	i = 0;
	while (splited[i + 1])
	{
		new_args[i] = ft_strdup(splited[i + 1], ptrs);
		i++;
	}
	if (old_args)
	{
		j = 0;
		while (old_args[j])
		{
			new_args[i] = ft_strdup(old_args[j++], ptrs);
			i++;
		}
	}
	new_args[i] = NULL;
	return (new_args);
}

void	move_options(t_cmd *cmd, t_free **ptrs)
{
	char	**splited;
	char	*tmp1;
	char	**tmp2;
	int		i;

	if (cmd->cmd && cmd->cmd_is_var && words_counts_2(cmd->cmd) > 1)
	{
		splited = ft_split_2(cmd->cmd, ptrs);
		tmp1 = cmd->cmd;
		tmp2 = cmd->args;
		cmd->cmd = ft_strdup(splited[0], ptrs);
		cmd->args = get_splited_args(cmd->args, splited, ptrs);
		ft_free_ptr(ptrs, tmp1);
		if (tmp2)
		{
			i = -1;
			while (tmp2[++i])
				ft_free_ptr(ptrs, tmp2[i]);
		}
		i = -1;
		while (splited[++i])
			ft_free_ptr(ptrs, splited[i]);
	}
}
