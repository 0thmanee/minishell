/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboutsli <yboutsli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 09:26:13 by yboutsli          #+#    #+#             */
/*   Updated: 2024/03/28 00:59:36 by yboutsli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cd_dir(char *str, t_list **list_env)
{
    char	*tmp;
    char	*tmp1;
    int		status;
	char	*cwd;
    DIR		*dir;

    status = 0;
	cwd = get_env(list_env, "PWD");
    tmp1 = ft_strjoin_2("/", str);
    tmp = ft_strjoin_2(cwd, tmp1);
    dir = opendir(str);
    if (dir)
    {
        chdir(str);
        closedir(dir);
    }
    else
    {
        perror(str);
        status = 1;
    }
	if (status == 0)
	{
		env_update(list_env, "PWD", str);
		env_update(list_env, "OLDPWD", cwd);
	}
    free(tmp);
    free(tmp1);
    return (status);
}

int	cd_root(char *str, t_list **list_env)
{
	int	status;
	char	*cwd;

	cwd = get_env(list_env, "PWD");
	status = 0;
	if (chdir(str) == -1)
	{
		printf("cd: no such file or directory: %s\n", str);
		status = 1;
	}
	else
	{
		env_update(list_env, "OLDPWD", cwd);
		env_update(list_env, "PWD", str);
	}
	return (status);
}

int	cd_home(t_list **env, char *str)
{
	char	*home;
	char	*cwd;

	cwd = get_env(env, "PWD");
	home = get_env(env, "HOME");
	if (!home)
	{
		printf("minishell: cd: HOME not set\n");//write(2)
		return (1);
	}
	else if (chdir(home) == -1)
	{
		perror(str);
		return (1);
	}
	else
	{
		env_update(env, "OLDPWD", cwd);
		env_update(env, "PWD", home);
	}
	return (0);
}

int	cd_oldpwd(t_list **env)
{
	char	*oldpwd;
	char	*cwd;
	int		status;

	status = 0;
	oldpwd = get_env(env, "OLDPWD");
	cwd = get_env(env, "PWD");
	if (!oldpwd)
	{
		printf("minishell: cd: OLDPWD not set\n");
		return (1);
	}
	else if (chdir(oldpwd) == -1)
	{
		perror("cd :");
		return (1);
	}
	else
	{
		env_update(env, "OLDPWD", cwd);
		env_update(env, "PWD", oldpwd);
	}
	return (status);
}

int	cd(char **args, t_list **env)
{
	char	*cwd;
	int		status;
	
	status = 0;
	if (args == NULL)
		status = cd_home(env, NULL);
	else if (args[0][0] == '/')
		status = cd_root(args[0], env);
	else if (args[0][0] == '-' && args[0][1] == '\0')
		status = cd_oldpwd(env);
	else
		status = cd_dir(args[0], env);
	return (status);
}
