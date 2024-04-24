/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouchta <obouchta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 16:20:23 by yboutsli          #+#    #+#             */
/*   Updated: 2024/04/24 06:43:19 by obouchta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*utils3(t_new_1 *new_strct, char *input)
{
	char	*tmp;

	tmp = input;
	input = parse_heredoc(input, new_strct->env, new_strct->ptrs);
	free(tmp);
	return (input);
}
void	handler_2(int sig)
{
	(void)sig;
	signal(SIGINT, SIG_DFL);
}
static void	utils(int fd[2], t_file *in, int mode, t_new_1 *new_strct)
{
	char	*input;

	signal(SIGINT, handler_2);
	rl_catch_signals = 1;
	if (mode)
		close(fd[0]);
	input = readline("> ");
	while (input != NULL && ft_strcmp(input, in->delimiter))
	{
		if (in->delim_flag && !check_braces(input))
			input = utils3(new_strct, input);
		if (mode)
			(write(fd[1], input, ft_strlen(input)), write(fd[1], "\n", 1));
		if (mode && ft_strchr(input, '{') && check_braces(input))
			write(fd[1], "minishell: bad substitution\n", 28);
		free(input);
		input = readline("> ");
	}
	if (mode)
		close (fd[1]);
	free(input);
	exit(0);
}

int	here_doc(t_file *infile, int mode, t_list *list_env, t_free **ptrs)
{
	int		pid;
	int		fd[2];
	int		status;
	t_new_1	tmp;

	tmp.env = list_env;
	tmp.ptrs = ptrs;
	if (mode && pipe(fd) == -1)
		(write(2, "minishell: ", 11), perror("pipe"), exit(1));
	pid = fork();
	if (pid < 0)
		(write(2, "minishell: ", 11), perror("Fork: "), exit(1));
	if (pid == 0)
		utils(fd, infile, mode, &tmp);
	if (mode)
		(dup2(fd[0], 0), close2(fd));
	waitpid(pid, &status, 0);
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
	{
		write(1, "\n", 1);
		return (1);
	}
	return (0);
}
