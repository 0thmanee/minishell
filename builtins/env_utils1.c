/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboutsli <yboutsli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 16:29:49 by yboutsli          #+#    #+#             */
/*   Updated: 2024/04/20 14:06:46 by yboutsli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	shlvl_error(int num, t_free **ptrs)
{
	char	*tmp;

	tmp = int_to_str(num, ptrs);
	ft_putstr_fd("minishell: warning: shell level (", 2);
	ft_putstr_fd(tmp, 2);
	ft_putstr_fd(") too high, resetting to 1\n", 2);
	ft_free_ptr(ptrs, tmp);
}

char	*shlvl_var1(int shlvl, t_free **ptrs)
{
	char	*tmp[2];

	tmp[0] = int_to_str(shlvl, ptrs);
	tmp[1] = ft_strjoin("SHLVL=", tmp[0], ptrs);
	ft_free_ptr(ptrs, tmp[0]);
	return (tmp[1]);
}

void	shlvl_var(t_list **env, t_free **ptrs)
{
	t_cmd	cmd;
	char	*arg[2];
	int		shlvl;
	char	*envp_shlvl;

	arg[0] = ft_strdup("SHLVL=1", ptrs);
	arg[1] = NULL;
	cmd.args = arg;
	envp_shlvl = getenv("SHLVL");
	if (!envp_shlvl || envp_shlvl[0] == '\0')
		(ft_free_ptr(ptrs, arg[0]), export(&cmd, env, ptrs));
	else
	{
		shlvl = (int)ft_atoi(envp_shlvl);
		if (shlvl >= 1000)
			shlvl_error(shlvl, ptrs);
		else if (shlvl < 0)
			(ft_free_ptr(ptrs, arg[0]), arg[0] = ft_strdup("SHLVL=0", ptrs));
		else if (shlvl == 999)
			(ft_free_ptr(ptrs, arg[0]), arg[0] = ft_strdup("SHLVL=", ptrs));
		else
			arg[0] = shlvl_var1(++shlvl, ptrs);
		export(&cmd, env, ptrs);
	}
	ft_free_ptr(ptrs, arg[0]);
}

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
		ft_lstadd_back_2(&env, ft_lstnew_2(var, value, ptrs));
		(ft_free_ptr(ptrs, var), ft_free_ptr(ptrs, value));
	}
	shlvl_var(&env, ptrs);
	return (env);
}

void	env_init1(t_list	**env, t_free **ptrs)
{
	char	*cwd;
	char	*tmp;
	char	*args[4];

	cwd = getcwd(NULL, 0);
	if (cwd != NULL)
	{
		args[0] = "PWD";
		args[1] = "_";
		args[2] = "OLDPWD";
		args[3] = NULL;
		unset(env, args, ptrs);
		ft_lstadd_back_2(env, ft_lstnew_2("PWD", cwd, ptrs));
		tmp = ft_strjoin(cwd, "/./minishell", ptrs);
		ft_lstadd_back_2(env, ft_lstnew_2("_", tmp, ptrs));
		ft_lstadd_back_2(env, ft_lstnew_2("OLDPWD", NULL, ptrs));
		ft_free_ptr(ptrs, tmp);
	}
	free(cwd);
}
