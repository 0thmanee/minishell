/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouchta <obouchta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 07:16:43 by obouchta          #+#    #+#             */
/*   Updated: 2024/03/08 06:36:44 by obouchta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	regonize_type(char *input, int i)
{
	if (input[i] == '<' && input[i + 1] == '<')
		return (HERE_DOC);
	if (input[i] == '<')
		return (INPUT);
	if (input[i] == '>' && input[i + 1] == '>')
		return (APPEND);
	if (input[i] == '>')
		return (OUTPUT);
	if (input[i] == '|')
		return (PIPE);
	return (EXPRESSION);
}

int	regonize_type_2(int prev_type)
{
	if (prev_type == INPUT)
		return (IN_FILE);
	if (prev_type == OUTPUT || prev_type == APPEND)
		return (OUT_FILE);
	if (prev_type == HERE_DOC)
		return (DELIMITER);
	return (CMD);
}

int get_last_type(t_token *tokens)
{
	t_token *curr;

	curr = tokens;
	if (!curr)
		return (-1);
	while (curr && curr->next)
		curr = curr->next;
	if (curr)
		return (curr->type);
	return (EXPRESSION);
}
