/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yasser03 <yasser03@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 09:26:13 by yboutsli          #+#    #+#             */
/*   Updated: 2024/03/14 03:28:06 by yasser03         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cd_dir(char *str, char *cwd)
{
	char	*tmp;
	char	*tmp1;
	int		status;

	status = 0;
	tmp1 = ft_strjoin("/", str);
	tmp = ft_strjoin(cwd, tmp1);
	if (access(str, F_OK) == 0)
		chdir(tmp);
	else
	{
		printf("cd: no such file or directory: %s\n", str);
		status = 1;
	}
	free(tmp);
	free(tmp1);
	return (status);
}

int	cd_root(char *str)
{
	int	status;

	status = 0;
	if (chdir(str) == -1)
	{
		printf("cd: no such file or directory: %s\n", str);
		status = 1;
	}
	return (status);
}

int	cd_home(t_list **env, char *str)
{
	char	*home;
	
	home = get_env(env, "HOME");
	if (!home)
	{
		printf("minishell: cd: HOME not set\n");
		return (1);
	}
	else if (chdir(home) == -1)
	{
		perror(str);
		return (1);
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
	if (!oldpwd)
	{
		printf("minishell: cd: OLDPWD not set\n");
		status = 1;
	}
	else
	{
		if (chdir(oldpwd) == -1)
		{
			perror("cd :");
			status = 1;
		}			
		cwd = getcwd(NULL, 0);
		printf("%s\n", cwd);
		free(cwd);
	}
	return (status);
}

int	cd(char **args, t_list **env)
{
	char	*cwd;
	int		status;

	status = 0;
	cwd = getcwd(NULL, 0);
	if (args == NULL)
		status = cd_home(env, NULL);
	else if (args[0][0] == '~' || !ft_strcmp(args[0], "--"))
		status = cd_home(env, args[0]);
	else if (args[0][0] == '/')
		status = cd_root(args[0]);
	else if (args[0][0] == '-' && args[0][1] == '\0')
		status = cd_oldpwd(env);
	else
		status = cd_dir(args[0], cwd);
	if (status == 0)
	{
		env_update(env, "OLDPWD", cwd);
		free(cwd);
		cwd = getcwd(NULL, 0);
		env_update(env, "PWD", cwd);
	}
	return (free(cwd), status);
}
