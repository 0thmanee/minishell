/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouchta <obouchta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 17:17:09 by obouchta          #+#    #+#             */
/*   Updated: 2024/04/25 02:28:23 by obouchta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	set_no_quote(char *value)
{
	int	i;

	i = 0;
	while (value[i])
	{
		if (value[i] == '\'' || value[i] == '\"')
			return (0);
		i++;
	}
	return (1);
}

int	no_quotes_len(char *cmd)
{
	int		len_indx[2];
	char	quote;

	len_indx[0] = ft_strlen(cmd);
	len_indx[1] = 0;
	if (!cmd)
		return (0);
	while (cmd[len_indx[1]])
	{
		if (cmd[len_indx[1]] == '\'' || cmd[len_indx[1]] == '\"')
		{
			len_indx[0]--;
			quote = cmd[len_indx[1]++];
			while (cmd[len_indx[1]] && cmd[len_indx[1]] != quote)
				len_indx[1]++;
			if (cmd[len_indx[1]])
			{
				len_indx[1]++;
				len_indx[0]--;
			}
		}
		else
			len_indx[1]++;
	}
	return (len_indx[0]);
}

char	*no_quoted_value(char *cmd, int len, t_free **ptrs)
{
	char	*new_cmd;
	int		indxs[2];
	char	quote;

	if (!cmd)
		return (NULL);
	indxs[0] = 0;
	indxs[1] = 0;
	new_cmd = ft_malloc(ptrs, len + 1);
	while (cmd[indxs[0]])
	{
		if (cmd[indxs[0]] == '\'' || cmd[indxs[0]] == '\"')
		{
			quote = cmd[indxs[0]++];
			while (cmd[indxs[0]] && cmd[indxs[0]] != quote)
				new_cmd[indxs[1]++] = cmd[indxs[0]++];
			if (cmd[indxs[0]])
				indxs[0]++;
		}
		else
			new_cmd[indxs[1]++] = cmd[indxs[0]++];
	}
	new_cmd[indxs[1]] = '\0';
	return (new_cmd);
}

void	remove_quotes_helper(t_token *curr, t_free **ptrs)
{
	int		i;
	char	*tmp;

	i = -1;
	while (++i < curr->args_len)
	{
		tmp = curr->args[i].value;
		curr->args[i].no_quote = set_no_quote(curr->args[i].value);
		curr->args[i].value = no_quoted_value(curr->args[i].value,
				no_quotes_len(curr->args[i].value), ptrs);
		ft_free_ptr(ptrs, tmp);
	}
}

void	remove_quotes(t_token **tokens, t_free **ptrs)
{
	t_token	*curr;
	char	*tmp;

	curr = *tokens;
	while (curr)
	{
		curr->no_quote = set_no_quote(curr->value);
		if (curr->type == CMD || curr->type == OUT_FILE
			|| curr->type == IN_FILE || curr->type == DELIMITER)
		{
			tmp = curr->value;
			curr->value = no_quoted_value(curr->value,
					no_quotes_len(curr->value), ptrs);
			ft_free_ptr(ptrs, tmp);
		}
		if (curr->args)
			remove_quotes_helper(curr, ptrs);
		curr = curr->next;
	}
}
