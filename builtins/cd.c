/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboutsli <yboutsli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 09:26:13 by yboutsli          #+#    #+#             */
/*   Updated: 2024/04/18 18:29:12 by yboutsli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	cd_dir_utils(t_list **list_env, char *pwd,
			char *tmp[2], t_free **ptrs)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (cwd)
	{
		if (!var_exist("OLDPWD", *list_env))
			env_update(list_env, "OLDPWD", pwd, ptrs);
		if (!var_exist("PWD", *list_env))
			env_update(list_env, "PWD", cwd, ptrs);
		free(cwd);
	}
	else
	{
		ft_putstr_fd("cd: error retrieving current directory: getcwd: "
			"cannot access parent directories: No such file or directory\n", 2);
		if (!var_exist("OLDPWD", *list_env))
			env_update(list_env, "OLDPWD", pwd, ptrs);
		if (!var_exist("PWD", *list_env))
			env_update(list_env, "PWD", tmp[1], ptrs);
	}
}

static int	cd_dir(char *str, t_list **list_env, t_free **ptrs)
{
	char	*tmp[2];
	int		status;
	char	*pwd;

	status = 0;
	pwd = get_env(list_env, "PWD", 0, ptrs);
	if (!last_bs(pwd))
		tmp[0] = ft_strdup(str, ptrs);
	else
		tmp[0] = ft_strjoin("/", str, ptrs);
	tmp[1] = ft_strjoin(pwd, tmp[0], ptrs);
	if (chdir(str) == 0)
		cd_dir_utils(list_env, pwd, tmp, ptrs);
	else
		status = new_perror(str);
	return (ft_free_ptr(ptrs, tmp[1]), ft_free_ptr(ptrs, tmp[0]), status);
}

static int	cd_root(char *str, t_list **list_env, t_free **ptrs)
{
	int		status;
	char	*cwd;
	char	*tmp;

	cwd = get_env(list_env, "PWD", 0, ptrs);
	status = 0;
	if (chdir(str) == -1)
	{
		ft_putstr_fd("cd: no such file or directory: ", 2);
		(ft_putstr_fd(str, 2), ft_putstr_fd("\n", 2));
		status = 1;
	}
	else
	{
		tmp = getcwd(NULL, 0);
		if (tmp)
		{
			if (!var_exist("OLDPWD", *list_env))
				env_update(list_env, "OLDPWD", cwd, ptrs);
			if (!var_exist("PWD", *list_env))
				env_update(list_env, "PWD", tmp, ptrs);
			free(tmp);
		}
	}
	return (status);
}

static int	cd_home(t_list **env, char *str, t_free **ptrs)
{
	char	*home;
	char	*cwd;

	cwd = get_env(env, "PWD", 0, ptrs);
	home = get_env(env, "HOME", 0, ptrs);
	if (!home)
	{
		ft_putstr_fd("minishell: cd: HOME not set\n", 2);
		return (1);
	}
	else if (chdir(home) == -1)
		return (write(2, "minishell: ", 11), perror(str), 1);
	else
	{
		if (!var_exist("OLDPWD", *env))
			env_update(env, "OLDPWD", cwd, ptrs);
		if (!var_exist("PWD", *env))
			env_update(env, "PWD", home, ptrs);
	}
	return (0);
}

int	cd(char **args, t_list **env, t_free **ptrs)
{
	int		status;

	status = 0;
	if (args == NULL)
		status = cd_home(env, NULL, ptrs);
	else if (args[0][0] == '/')
		status = cd_root(args[0], env, ptrs);
	else
		status = cd_dir(args[0], env, ptrs);
	return (status);
}
