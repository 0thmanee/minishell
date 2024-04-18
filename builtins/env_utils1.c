/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboutsli <yboutsli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 16:29:49 by yboutsli          #+#    #+#             */
/*   Updated: 2024/04/18 21:49:21 by yboutsli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*env_lst(char **envp, t_free **ptrs)
{
	int		i;
	int		j;
	char	*var;
	char	*value;
	t_list	*env;

	env = NULL;
	i = -1;
	while (envp[++i])
	{
		if (!ft_strncmp(envp[i], "OLDPWD", 6))
			continue ;
		j = 0;
		while (envp[i][j] && envp[i][j] != '=')
			j++;
		var = ft_substr(envp[i], 0, j, ptrs);
		value = ft_substr(envp[i], j + 1, ft_strlen(envp[i]), ptrs);
		ft_lstadd_back_2(&env, ft_lstnew_2(var, value, 0, ptrs));
		(ft_free_ptr(ptrs, var), ft_free_ptr(ptrs, value));
	}
	return (env);
}

void	env_init1(t_list	**env, t_free **ptrs)
{
	char	*cwd;
	char	*tmp;
	char	*args[5];

	cwd = getcwd(NULL, 0);
	if (cwd != NULL)
	{
		args[0] = "PATH";
		args[1] = "PWD";
		args[2] = "_";
		args[3] = "OLDPWD";
		args[4] = NULL;
		unset(env, args, ptrs);
		ft_lstadd_back_2(env, ft_lstnew_2("PATH",
				"/usr/gnu/bin:/usr/local/bin:/bin:/usr/bin:.", 1, ptrs));
		ft_lstadd_back_2(env, ft_lstnew_2("PWD", cwd, 0, ptrs));
		tmp = ft_strjoin(cwd, "/./minishell", ptrs);
		ft_lstadd_back_2(env, ft_lstnew_2("_", tmp, 0, ptrs));
		ft_lstadd_back_2(env, ft_lstnew_2("OLDPWD", NULL, 0, ptrs));
		ft_free_ptr(ptrs, tmp);
	}
	free(cwd);
}
