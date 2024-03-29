/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouchta <obouchta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 16:20:23 by yboutsli          #+#    #+#             */
/*   Updated: 2024/03/29 02:34:34 by obouchta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	here_doc_utils(int fd[2], char *delimiter, int mode)
{
	char	*input;

	if (mode)
		close(fd[0]);
	input = readline("> ");
	while(input != NULL && ft_strcmp(input, delimiter))
	{
		if (mode)
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

void	here_doc(char *delimiter, int mode)
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
		here_doc_utils(fd, delimiter, mode);
	if (mode)
	{
		dup2(fd[0], 0);
		close2(fd);
	}
	waitpid(pid, NULL, 0);
}