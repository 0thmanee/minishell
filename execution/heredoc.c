/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouchta <obouchta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 16:20:23 by yboutsli          #+#    #+#             */
/*   Updated: 2024/04/03 21:52:51 by obouchta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*parse_heredoc(char *input, t_list *list_env, t_free **ptrs)
{
	int	i;
	char *result;

	(i = 0, result = ft_strdup(input, ptrs));
	while (result[i])
	{
		if (result[i] == '$' && !result[i + 1])
			return (result);
		if (result[i] == '$')
		{
			if (result[i + 1] == '\"' || result[i + 1] == '\''
				|| (ft_isalpha(result[i + 1]) && result[i + 1] != '_'
				&& ft_isdigit(result[i + 1])))
			{
				i++;
				continue ;
			}
			else if (result[i + 1] == '{')
				result = case_4(result, &i, list_env, ptrs);
			else if (!ft_isdigit(result[i + 1]))
				result = case_3(result, &i, ptrs);
			else
				result = case_1(result, &i, list_env, ptrs);
			if (!result)
				return (NULL);
		}
		if (i >= ft_strlen(result))
			break ;
		else if (result[i] == '$')
			continue;
		i++;
	}
	return (result);
}

static void	here_doc_utils(int fd[2], t_file *infile, int mode, t_list *list_env, t_free **ptrs)
{
	char	*input;
	char	*tmp;

	signal(SIGINT, SIG_DFL);
	rl_catch_signals = 1;
	if (mode)
		close(fd[0]);	
	input = readline("> ");
	while(input != NULL && ft_strcmp(input, infile->delimiter))
	{
		if (infile->delim_flag && !check_braces(input))
			(tmp = input, input = parse_heredoc(input, list_env, ptrs), free(tmp));
		if (mode)
			(write(fd[1], input, ft_strlen(input)), write(fd[1], "\n", 1));
		if (mode && ft_strchr(input, '{') && check_braces(input))
			write(fd[1], "minishell: bad substitution\n", 28);
		free(input);
		input = readline("> ");
	}
	if (mode)
		close (fd[1]);
	(free(input), exit(0));
}

int	here_doc(t_file *infile, int mode, t_list *list_env, t_free **ptrs)
{
	int	pid;
	int	fd[2];
	int	status;


	if (mode && pipe(fd) == -1)
	{
		perror("pipe");
		exit(1);
	}
	pid = fork();
	if (pid < 0)
	{
		perror("Fork: ");
		exit(1);
	}
	if (pid == 0)
		here_doc_utils(fd, infile, mode, list_env, ptrs);
	if (mode)
	{
		dup2(fd[0], 0);
		close2(fd);
	}
	waitpid(pid, &status, 0);
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
		return (1);
	return (0);
}
