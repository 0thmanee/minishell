/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouchta <obouchta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 16:20:23 by yboutsli          #+#    #+#             */
/*   Updated: 2024/03/29 21:22:40 by obouchta         ###   ########.fr       */
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
		if (result[i] == '$' && result[i + 1])
		{
			if (input[i + 1] == '\'' || input[i + 1] == '\"')
				result = case_2(result, &i, ptrs);
			else if (ft_isalpha(input[i + 1]) && input[i + 1] != '_')
				result = case_3(result, &i, ptrs);
			else if (input[i + 1] == '{')
				result = case_4(result, &i, list_env, ptrs);
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

	if (mode)
		close(fd[0]);
	input = readline("> ");
	while(input != NULL && ft_strcmp(input, infile->delimiter))
	{
		if
			(tmp = input, input = parse_heredoc(input, list_env, ptrs), free(tmp));
		if (mode) (infile->delim_flag)
		{
			write(fd[1], input, strlen(input));
			write(fd[1], "\n", 1);
		}
		free(input);
		input = readline("> ");
    }
	free(input);
	exit(0);
}

void	here_doc(t_file *infile, int mode, t_list *list_env, t_free **ptrs)
{
	int	pid;
	int	fd[2];

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
	waitpid(pid, NULL, 0);
}
