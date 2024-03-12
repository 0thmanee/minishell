/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yasser03 <yasser03@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 09:26:13 by yboutsli          #+#    #+#             */
/*   Updated: 2024/03/12 04:45:31 by yasser03         ###   ########.fr       */
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
		printf("minishell: %s: %s\n", strerror(errno), str + 1);
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

int	cd(char *str, t_list **env)
{
	char	*cwd;
	int		status;

	status = 0;
	cwd = getcwd(NULL, 0);
	// printf ("old_pwd = %s\n", cwd);
	if (!str || !str[0] || str[0] == '~' || !ft_strcmp(str, "--") || str[0] == ' ')
		status = cd_home(env, str);
	else if (str[0] == '/')
		status = cd_root(str);
	else if (str[0] == '-' && str[1] == '\0')
		status = cd_oldpwd(env);
	else if (str != NULL)
		status = cd_dir(str, cwd);
	if (status == 0)
	{
		env_update(env, "OLDPWD", cwd);
		free(cwd);
		cwd = getcwd(NULL, 0);
		env_update(env, "PWD", cwd);
		// printf ("new_pwd = %s\n", cwd);
	}
	return (free(cwd), status);
}
