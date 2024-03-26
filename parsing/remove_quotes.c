/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouchta <obouchta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 17:17:09 by obouchta          #+#    #+#             */
/*   Updated: 2024/03/26 03:29:39 by obouchta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	barces_len(char *cmd, int *i, int *len)
{
	if ((quoted(cmd, *i) == '\"' || !quoted(cmd, *i))
		&& *i > 0 && cmd[*i - 1] == '$' && cmd[*i] == '{')
	{
		(*len) -= 2;
		while (cmd[*i] && cmd[*i] != '}')
			(*i)++;
		(*i)++;
		return (1);
	}
	return (0);
}

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
		else if (barces_len(cmd, &i, &len))
			continue ;
		else
			i++;
	}
	return (len);
}

int	barces_remmover(char *cmd, char *new_cmd, int *i, int *j)
{
	if ((quoted(cmd, *i) == '\"' || !quoted(cmd, *i))
		&& *i > 0 && cmd[*i - 1] == '$' && cmd[*i] == '{')
	{
		(*i)++;
		while (cmd[*i] && cmd[*i] != '}')
			new_cmd[(*j)++] = cmd[(*i)++];
		(*i)++;
		return (1);
	}
	return (0);
}

char	*no_quoted_value(char *cmd, int len, t_free **ptrs)
{
	char	*new_cmd;
	int		i;
	int		j;
	char	quote;

	(i = 0, j = 0, new_cmd = ft_malloc(ptrs, len + 1));
	if (!new_cmd)
		(ft_free_all(ptrs), exit(1));
	while (cmd[i])
	{
		if (cmd[i] == '\'' || cmd[i] == '\"')
		{
			quote = cmd[i++];
			while (cmd[i] != quote)
				new_cmd[j++] = cmd[i++];
			i++;
		}
		else if (barces_remmover(cmd, new_cmd, &i, &j))
			continue ;
		else
			new_cmd[j++] = cmd[i++];
	}
	new_cmd[j] = '\0';
	return (new_cmd);
}

int	remove_quotes(t_token **tokens, t_free **ptrs)
{
	t_token	*curr;
	char	*tmp;
	int		i;

	curr = *tokens;
	while (curr)
	{
		if (curr->type == CMD || curr->type == OUT_FILE
			|| curr->type == IN_FILE || curr->type == DELIMITER)
			(tmp = curr->value, curr->value = no_quoted_value(curr->value,
				no_quotes_len(curr->value), ptrs), ft_free_ptr(ptrs, tmp));
		if (curr->args)
		{
			i = -1;
			while (++i < curr->args_len)
				(tmp = curr->args[i].value, 
				curr->args[i].value = no_quoted_value(curr->args[i].value,
					no_quotes_len(curr->args[i].value), ptrs), ft_free_ptr(ptrs, tmp));
		}
		curr = curr->next;
	}
	return (1);
}
