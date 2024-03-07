/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouchta <obouchta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 17:17:09 by obouchta          #+#    #+#             */
/*   Updated: 2024/03/07 17:17:40 by obouchta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	no_quotes_len(char *cmd)
{
	int	len;
	int	i;
	char	quote;
	
	len = ft_strlen(cmd);
	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == '\'' || cmd[i] == '\"')
		{
			len -= 2;
			quote = cmd[i++];
			while (cmd[i] && cmd[i] != quote)
				i++;
			i++;
		}
		else
			i++;
	}
	return (len);
}

char	*no_quoted_value(char *cmd, int len)
{
	char	*new_cmd;
	int		i;
	int		j;
	char	quote;

	i = 0;
	j = 0;
	new_cmd = malloc(len + 1);
	if (!new_cmd)
		return (NULL);
	while (cmd[i])
	{
		if (cmd[i] == '\'' || cmd[i] == '\"')
		{
			quote = cmd[i++];
			while (cmd[i] != quote)
				new_cmd[j++] = cmd[i++];
			i++;
		}
		else
			new_cmd[j++] = cmd[i++];
	}
	new_cmd[j] = '\0';
	return (new_cmd);
}

int	remove_quotes(t_token **tokens)
{
	t_token	*curr;
	int		i;

	curr = *tokens;
	while (curr)
	{
		if (curr->type == CMD || curr->type == OUT_FILE
			|| curr->type == IN_FILE || curr->type == DELIMITER)
		{
			curr->value = no_quoted_value(curr->value, no_quotes_len(curr->value));
			if (!curr->value)
				return (0);
		}
		if (curr->args)
		{
			i = 0;
			while (curr->args[i])
			{
				curr->args[i] = no_quoted_value(curr->args[i], no_quotes_len(curr->args[i]));
				i++;
			}
		}
		curr = curr->next;
	}
	return (1);
}
