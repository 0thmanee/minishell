/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouchta <obouchta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 10:58:53 by obouchta          #+#    #+#             */
/*   Updated: 2024/03/03 02:38:04 by obouchta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*join_input(char **splited, int words_nbr)
{
	char	*joined;
	int		total_len;
	int		i;

	total_len = 0;
	i = -1;
	while (splited[++i])
		total_len += ft_strlen(splited[i]);
	total_len += (words_nbr - 1);
	joined = (char *)malloc(total_len + 1);
	if (!joined)
		return (NULL);
	i = -1;
	while (splited[++i])
	{
		ft_strlcat(joined, splited[i], total_len + 1);
		if (splited[i + 1])
			ft_strlcat(joined, " ", total_len + 1);
	}
	return (joined);
}

int define_token_type(char *token)
{
	if (!ft_strcmp(token, ";"))
		return (SEMICOLON);
	if (!ft_strcmp(token, "&&"))
		return (AND);
	if (!ft_strcmp(token, "||"))
		return (OR);
	if (!ft_strcmp(token, "|"))
		return (PIPE);
	if (!ft_strcmp(token, ">"))
		return (OUTPUT);
	if (!ft_strcmp(token, ">>"))
		return (APPEND);
	if (!ft_strcmp(token, "<"))
		return (INPUT);
	if (!ft_strcmp(token, "<<"))
		return (HERE_DOC);
	if (!ft_strcmp(token, "("))
		return (OPEN_PAREN);
	if (!ft_strcmp(token, ")"))
		return (CLOSE_PAREN);
	return (EXPRESSION);
}

void	fill_tokens(t_token *tokens, char **splited, int words_nbr)
{
	int	i;

	i = -1;
	while (++i < words_nbr)
	{
		tokens[i].value = splited[i];
		tokens[i].type = define_token_type(splited[i]);
	}
	tokens[i].value = NULL;
	tokens[i].type = -1;
}

