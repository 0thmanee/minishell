/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboutsli <yboutsli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 16:20:23 by yboutsli          #+#    #+#             */
/*   Updated: 2024/03/27 16:20:58 by yboutsli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	here_doc_utils(int fd[2], t_cmd *cmd)
{
	char	*input;

	close(fd[0]);
	input = readline("> ");
	while(input != NULL && ft_strcmp(input, cmd->infiles->delimiter)) 
	{
        write(fd[1], input, strlen(input));
        write(fd[1], "\n", 1);
        free(input);
		input = readline("> ");
    }
	free(input);
	exit(0);
}

void	here_doc(t_cmd *cmd)
{
	int	pid;
	int	fd[2];

	if (pipe(fd) == -1)
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
		here_doc_utils(fd, cmd);
	dup2(fd[0], 0);
	close2(fd);
	waitpid(pid, NULL, 0);
}