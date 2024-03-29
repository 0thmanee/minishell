/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouchta <obouchta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 09:26:13 by yboutsli          #+#    #+#             */
/*   Updated: 2024/03/29 03:57:11 by obouchta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	last_bs(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	if (i >= 1 && str[i - 1] == '/')
		return (0);
	return(1);
}
int	cd_dir(char *str, t_list **list_env)
{
	char	*tmp[3];
	int		status;
	char	*pwd;
	char	*cwd;

	status = 0;
	pwd = get_env(list_env, "PWD");
	if (!last_bs(pwd))
		tmp[0] = ft_strdup_1(str);
	else
		tmp[0] = ft_strjoin_2("/", str);
	tmp[1] = ft_strjoin_2(pwd, tmp[0]);
	if (chdir(str) == 0)
	{
		cwd = getcwd(NULL, 0);
		if (cwd)
		{
			env_update(list_env, "OLDPWD", pwd);
			env_update(list_env, "PWD", cwd);
			free(cwd);
		}
		else
		{
			perror("getcwd: ");
			env_update(list_env, "PWD", tmp[1]);
			env_update(list_env, "OLDPWD", pwd);
		}
	}
	else
	{
		perror(str);
		status = 1;
	}
	free(tmp[1]);
	free(tmp[0]);
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
