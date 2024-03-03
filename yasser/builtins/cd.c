/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboutsli <yboutsli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 09:26:13 by yboutsli          #+#    #+#             */
/*   Updated: 2024/03/02 21:24:38 by yboutsli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
void l()
{
	system("leaks minishell");
}
char	*get_env(t_list **head, char *env_var)
{
	t_list	*current;
	char	*env_values;
	current = *head;
	while (current)
	{
		if (!ft_strncmp(current->content, env_var, ft_strlen(env_var)))
		{
			env_values = ft_substr(current->content, ft_strlen(env_var) + 1, ft_strlen(current->content) - (ft_strlen(env_var) + 1));
			return(env_values);
		}
		current = current->next;
	}
	return (NULL);
}
int	env_update(t_list **head, char *env_var, char *new)
{
	t_list	*current;
	char	*tmp;

	current = *head;
	while (current)
	{
		if (!ft_strncmp(current->content, env_var, ft_strlen(env_var)))
		{
			free(current->content);
			tmp = ft_strjoin("=",new); 
			current->content = ft_strjoin(env_var,tmp);
			free(tmp);
			return(0);
		}
		current = current->next;
	}
	return(1);
}
int	cd(char *str, t_list **env)
{
	char	buffer[BUFFER_SIZE];
	char	*cwd;
	char	*oldpwd;
	char 	*tmp;
	char	*tmp1;
	cwd = getcwd(NULL, 0);
	printf ("old_pwd = %s\n", cwd);
	if (str[0] == '~' || !ft_strcmp(str, "--"))
	{
		if (str[1] == '?')
		{
			printf("minishell: no matches found: %s\n", str);
			return (1);
		}
		else if (str[1] == '/' || str[1] == '\0' || !ft_strcmp(str, "--"))
			chdir(getenv("HOME"));
		else if (chdir(str) == -1)
		{
			printf("minishell: %s: %s\n", strerror(errno),str + 1);
			return (1);
		}
	}
	else if (str[0] == '-' && str[1] == '\0')
	{
		oldpwd = get_env(env, "OLDPWD");
		chdir(oldpwd);
		if (!ft_strcmp(oldpwd, "/Users/yboutsli"))
			printf("~\n");
		else
		{
			tmp = ft_substr(oldpwd, 15, ft_strlen(oldpwd) - 15);
			printf("|~%s|\n",tmp);
			free(tmp);
		}
		free(oldpwd);
	}
	else if (str != NULL)
	{
		tmp1 =ft_strjoin("/", str);
		tmp = ft_strjoin(cwd,tmp1);
		printf("%s\n", tmp);
		if (access(str, F_OK) == 0)
			chdir(tmp);
		else
			printf("cd: no such file or directory: %s\n", str);
		free(tmp);
	}
	else
	{
		printf("cd: no such file or directory: %s\n",str);
		return (1);
	}
	env_update(env,"OLDPWD", cwd);
	free(cwd);
	cwd = getcwd(NULL, 0);
	env_update(env,"PWD", cwd);
	printf ("new_pwd = %s\n", cwd);
	free(cwd);
	return (0);
}



t_list	*env_lst(char **envp)
{
	int	i;
	t_list	*env;

	env = NULL;
	i = -1;
	while (envp[++i])
		ft_lstadd_back(&env, ft_lstnew(envp[i]));
	return (env);
}
int main(int argc, char **argv, char **envp)
{
	char	*input;
	t_list	*env;
	t_list	*current;

	// atexit(l);
	env = env_lst(envp);
	input = readline("");
	while (input)
	{
		cd(input, &env);
		free(input);
		input = readline("");
	}
	free(input);
	ft_lstfree(&env);
	return (0);
	// printf ("[%d]\n", access("/..", F_OK);
}
