/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboutsli <yboutsli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 09:26:13 by yboutsli          #+#    #+#             */
/*   Updated: 2024/03/31 02:28:24 by yboutsli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
int	new_perror(char *str)
{
	perror(str);
	return (1);
}
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
void	cd_dir_utils(t_list **list_env, char *pwd, char *tmp[2])
{
	char	*cwd;

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
int	cd_dir(char *str, t_list **list_env)
{
	char	*tmp[3];
	int		status;
	char	*pwd;

	status = 0;
	pwd = get_env(list_env, "PWD");
	if (!last_bs(pwd))
		tmp[0] = ft_strdup_1(str);
	else
		tmp[0] = ft_strjoin_2("/", str);
	tmp[1] = ft_strjoin_2(pwd, tmp[0]);
	if (chdir(str) == 0)
		cd_dir_utils(list_env, pwd, tmp);
	else
		status = new_perror(str);
	return (free(tmp[1]), free(tmp[0]), status);
}

int	cd_root(char *str, t_list **list_env)
{
	int	status;
	char	*cwd;

	cwd = get_env(list_env, "PWD");
	status = 0;
	if (chdir(str) == -1)
	{
		ft_putstr_fd("cd: no such file or directory: ", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd("\n", 2);
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
		ft_putstr_fd("minishell: cd: HOME not set\n", 2);
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
	char	*cwd[2];
	int		status;

	status = 0;
	oldpwd = get_env(env, "OLDPWD");
	cwd[0] = get_env(env, "PWD");
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
		cwd[1] = ft_strdup_1(cwd[0]);
		env_update(env, "PWD", oldpwd);
		env_update(env, "OLDPWD", cwd[1]);
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
