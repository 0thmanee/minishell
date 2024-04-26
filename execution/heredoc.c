/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouchta <obouchta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 16:20:23 by yboutsli          #+#    #+#             */
/*   Updated: 2024/04/26 15:33:01 by obouchta         ###   ########.fr       */
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

void	join_input(char **str, char *input, t_free **ptrs)
{
	char	*tmp;

	tmp = *str;
	*str = ft_strjoin(*str, input, ptrs);
	ft_free_ptr(ptrs, tmp);
	tmp = *str;
	*str = ft_strjoin(*str, "\n", ptrs);
	ft_free_ptr(ptrs, tmp);
}

void	write_in_file(t_file *in, char *str, t_free **ptrs)
{
	unlink(in->file);
	in->fd = open(in->file, O_CREAT | O_TRUNC | O_RDWR, 0644);
	if (in->fd == -1)
		(write(2, "minishell: ", 11), perror(in->file));
	ft_putstr_fd(str, in->fd);
	ft_free_ptr(ptrs, str);
	close(in->fd);
}

static void	utils(t_file *in, t_new_1 *new_strct, t_free **ptrs)
{
	char	*input;
	char	*str;

	signal(SIGINT, &heredoc_sig);
	str = NULL;
	input = readline("> ");
	while (input != NULL && ft_strcmp(input, in->delimiter))
	{
		if (in->no_quote && !check_braces(input))
			input = utils3(new_strct, input);
		join_input(&str, input, ptrs);
		if (ft_strchr(input, '{') && check_braces(input))
			join_input(&str, "minishell: bad substitution", ptrs);
		if (in->no_quote)
			ft_free_ptr(new_strct->ptrs, input);
		else
			free(input);
		input = readline("> ");
	}
	free(input);
	write_in_file(in, str, ptrs);
}

int	here_doc(t_file *file, t_list *list_env, t_free **ptrs)
{
	t_new_1	tmp;
	int		original_stdin;

	tmp.env = list_env;
	tmp.ptrs = ptrs;
	original_stdin = dup(0);
	utils(file, &tmp, ptrs);
	if (g_signum == SIGINT)
	{
		g_signum = 0;
		(dup2(original_stdin, 0), close(original_stdin));
		exit_status(0, 1);
		signal(SIGINT, &handle_signals);
		return (1);
	}
	dup2(original_stdin, 0);
	close(original_stdin);
	signal(SIGINT, &handle_signals);
	return (0);
}
