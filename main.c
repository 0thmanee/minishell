/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouchta <obouchta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 08:42:35 by obouchta          #+#    #+#             */
/*   Updated: 2024/03/03 02:26:35 by obouchta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int	check_syntax(char *cmd)
// {
// 	// "" () 
// 	int	i;
	
// 	i = 0;
// 	while (cmd[i])
// 	{
// 		if (cm)
// 	}
// 	return (1);
// }
int	closed_quote(char *input)
{
	int	i;
	int	signle_q;
	int	double_q;

	i = 0;
	signle_q = 0;
	double_q = 0;
	while (input[i])
	{
		if (input[i] == '\"')
			double_q++;
		if (input[i] == '\'')
			signle_q++;
		i++;
	}
	return (!(double_q % 2) && !(signle_q % 2));
}

int	process_input(char *input)
{
	char	**splited_input;
	t_token	*tokens;

	if (!closed_quote(input))
		return (0);
	splited_input = ft_split(input, ' ');
	if (!splited_input)
		return (0);
	tokens = malloc(sizeof(t_token) * (count_words(input, ' ') + 1));
	if (!tokens)
		return (0);
	fill_tokens(tokens, splited_input, count_words(input, ' ') + 1);
	return (1);
}

int main()
{
	char	*cwd;
	char	*input;

	cwd = malloc(BUFFER_SIZE);
	if (!cwd)
		perror("error");
	if (getcwd(cwd, BUFFER_SIZE))
		cwd = ft_strjoin(cwd, " » ");
	else
		(perror("error"), free(cwd));
	using_history();
	while ((input = readline(cwd)) != NULL)
	{
		if (input[0])
			add_history(input);
		else
			ft_strcpy(input, history_get(history_length)->line);
		if (!process_input(input))
			printf("failed\n");
		free(input);
	}
	return (free(input), free(cwd), 0);
}
