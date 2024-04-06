/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouchta <obouchta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 03:10:42 by obouchta          #+#    #+#             */
/*   Updated: 2024/04/06 07:38:05 by obouchta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	syntax_error(t_token *token, int *here_doc)
{
	if (token->type == PIPE)
		return (1);
	while (token)
	{
		if (token->type == HERE_DOC && token->next
			&& token->next->type == DELIMITER)
			(*here_doc)++;
		if (token->type == INPUT || token->type == OUTPUT
			|| token->type == APPEND || token->type == HERE_DOC)
		{
			if (!token->next || token->next->type == INPUT
				|| token->next->type == OUTPUT || token->next->type == APPEND
				|| token->next->type == PIPE || token->next->type == HERE_DOC)
				return (1);
		}
		else if (token->type == PIPE
			&& (!token->next || token->next->type == PIPE))
			return (1);
		else if (invalid_braces(token))
			return (1);
		token = token->next;
	}
	return (0);
}

void	read_from_heredoc(t_token *curr, int *pid, int *here_doc)
{
	char	*ln;
	int		id;

	if (curr->type == HERE_DOC && *here_doc > 0)
	{
		id = fork();
		if (id == 0)
		{
			signal(SIGINT, SIG_DFL);
			rl_catch_signals = 1;
			while (1)
			{
				ln = readline("> ");
				if (!ln || (curr->next && !ft_strcmp(ln, curr->next->value)))
					break ;
				free(ln);
			}
			(free(ln), exit(EXIT_SUCCESS));
		}
		else
		{
			*pid = id;
			(*here_doc)--;
		}
	}
}

void	open_heredoc(t_token *tokens, int here_doc, int *s_error)
{
	t_token	*curr;
	int		pid;
	int		status;

	curr = tokens;
	while (curr && here_doc)
	{
		read_from_heredoc(curr, &pid, &here_doc);
		curr = curr->next;
		waitpid(pid, &status, 0);
		if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
		{
			(*s_error) = 0;
			break ;
		}
	}
}
