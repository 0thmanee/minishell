/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouchta <obouchta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 03:10:42 by obouchta          #+#    #+#             */
/*   Updated: 2024/04/03 21:52:51 by obouchta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_braces(char *value)
{
	int	i;

	i = 0;
	while (value[i])
	{
		if ((quoted(value, i) == '\"' || !quoted(value, i))
			&& value[i] == '$' && value[i + 1] && value[i + 1] == '{')
		{
			i += 2;
			if (!value[i] || value[i] == '{' || value[i] == '}'
				|| value[i] == '\"')
				return (1);
			else
			{
				while (value[i] && value[i] != '}' && value[i] != '\"')
				{
					if (is_whitespace(value[i]) || char_is_valid(value[i])
						|| value[i] == '{' || value[i++] == '$')
						return (1);
				}
				if (value[i] != '}')
					return (1);
			}
			continue ;
		}
		i++;
	}
	return (0);
}

int	invalid_braces(t_token *curr)
{
	int	i;

	i = 0;
	if (curr->value && ft_strchr(curr->value, '{') && check_braces(curr->value))
		return (1);
	if (curr->args_len)
	{
		while (i < curr->args_len)
		{
			if (ft_strchr(curr->value, '{') && check_braces(curr->args[i].value))
				return (1);
			i++;
		}
	}
	return (0);
}

int	syntax_error(t_token *tokens, int *here_doc)
{
	t_token *curr;
	int		type;

	curr = tokens;
	if (curr->type == PIPE)
		return (1);
	while (curr)
	{
		if (curr->type == HERE_DOC && curr->next && curr->next->type == DELIMITER)
			(*here_doc)++;
		type = curr->type;
		if (type == INPUT || type == OUTPUT || type == APPEND || type == HERE_DOC)
		{
			if (!curr->next || curr->next->type == INPUT || curr->next->type == OUTPUT
				|| curr->next->type == APPEND || curr->next->type == PIPE || curr->next->type == HERE_DOC)
				return (1);
		}
		else if (type == PIPE && (!curr->next || curr->next->type == PIPE))
			return (1);
		else if (invalid_braces(curr))
			return (1);
		curr = curr->next;
	}
	return (0);
}

void	read_from_heredoc(t_token *curr, int *pid, int *here_doc)
{
	char	*line;
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
				line = readline("> ");
				if (!line || (curr->next && !strcmp(line, curr->next->value)))
					break;
				free(line);
			}
			(free(line), exit(EXIT_SUCCESS));
		}
		else
		{
			*pid = id;
			(*here_doc)--;
		}
	}
}

void open_heredoc(t_token *tokens, int here_doc, int *s_error)
{
    t_token *curr;
	int	pid;
	int	status;

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
