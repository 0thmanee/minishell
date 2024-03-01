/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouchta <obouchta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 08:42:35 by obouchta          #+#    #+#             */
/*   Updated: 2024/03/01 15:26:32 by obouchta         ###   ########.fr       */
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

int	process_input(char *input)
{
	char	**splited_input;
	char	*joined_input;

	splited_input = ft_split(input, ' ');
	if (!splited_input)
		return (0);
	joined_input = join_input(splited_input, count_words(input, ' '));
	printf("<%s>\n", joined_input);
	if (!joined_input)
		return (0);
	// if (!check_syntax(joined_input))
	// 	return (-1);
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
		printf(ANSI_COLOR_CYAN "\n%s » ", cwd);
	else
		(perror("error"), free(cwd));
	input = readline("");
	while (input)
	{
		if (!process_input(input))
			perror("error");
		if (getcwd(cwd, BUFFER_SIZE))
		printf(ANSI_COLOR_CYAN "%s » ", cwd);
		else
			(perror("error"), free(cwd), free(input));
		input = readline("");
	}
	return (0);
}
