/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboutsli <yboutsli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 09:26:13 by yboutsli          #+#    #+#             */
/*   Updated: 2024/04/05 14:52:15 by yboutsli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
int	new_perror(char *str)
{
	write(2, "minishell: ", 11);
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
void	cd_dir_utils(t_list **list_env, char *pwd, char *tmp[2], t_free **ptrs)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (cwd)
	{
		env_update(list_env, "OLDPWD", pwd, ptrs);
		env_update(list_env, "PWD", cwd, ptrs);
		free(cwd);
	}
	else
	{
		ft_putstr_fd("cd: error retrieving current directory: getcwd: cannot access parent directories: No such file or directory\n", 2);
		env_update(list_env, "OLDPWD", pwd, ptrs);
		env_update(list_env, "PWD", tmp[1], ptrs);
	}
}
int	cd_dir(char *str, t_list **list_env, t_free **ptrs)
{
	char	*tmp[2];
	int		status;
	char	*pwd;

	status = 0;
	pwd = get_env(list_env, "PWD");
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

int	cd_root(char *str, t_list **list_env, t_free **ptrs)
{
	int		status;
	char	*cwd;
	char	*tmp;

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
		tmp = getcwd(NULL, 0);
		if (tmp)
		{	
			env_update(list_env, "OLDPWD", cwd, ptrs);
			env_update(list_env, "PWD", tmp, ptrs);
			free(tmp);
		}
	}
	return (status);
}

int	cd_home(t_list **env, char *str, t_free **ptrs)
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
		return (write(2, "minishell: ", 11), perror(str), 1);
	else
	{
		env_update(env, "OLDPWD", cwd, ptrs);
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
