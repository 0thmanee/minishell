/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouchta <obouchta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 08:42:35 by obouchta          #+#    #+#             */
/*   Updated: 2024/03/06 07:23:43 by obouchta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// add spaces when finding opearators x
// split the input into tokens x
// check if the tokens are valid x
// execute the command
// Create builtins
// handle signals
// check exit status
// check for leaks


void	print_the_shit(t_token *tokens)
{
	t_token *curr = tokens;
	while (curr)
	{
		printf("value: ( %s )\n", curr->value);
		printf("type: ");
		if (curr->type == CMD)
			printf("CMD\n");
		else if (curr->type == INPUT)
			printf("INPUT\n");
		else if (curr->type == IN_FILE)
			printf("IN_FILE\n");
		else if (curr->type == OUTPUT)
			printf("OUTPUT\n");
		else if (curr->type == OUT_FILE)
			printf("OUT_FILE\n");
		else if (curr->type == HERE_DOC)
			printf("HERE_DOC\n");
		else if (curr->type == DELIMITER)
			printf("DELIMITER\n");
		else if (curr->type == APPEND)
			printf("APPEND\n");
		else if (curr->type == PIPE)
			printf("PIPE\n");
		if (curr->args && *curr->args)
		{
				printf("args:\n");
				while (curr->args && *curr->args)
				{
					printf("{ %s }\n", *curr->args);
					curr->args++;
				}	
		}
		printf("\n");
		curr = curr->next;
	}
}

void	ft_split(char *input, t_token **tokens)
{
	t_token	*new_token;
	int		i;

	i = 0;
	while (input[i])
	{
		if (i == 0 || input[i] == ' ')
		{
			while (input[i] && input[i] == ' ')
				i++;
			if (i == ft_strlen(input))
				break ;
			if (input[i] && (input[i] == '\'' || input[i] == '\"'))
				new_token = get_quoted(input, &i, get_last_type(*tokens));
			else if (regonize_type(input, i) != EXPRESSION)
				new_token = get_token(input, &i, regonize_type(input, i));
			else
				new_token = get_cmd(input, &i, get_last_type(*tokens));
			if (new_token)
				ft_lstadd_back(tokens, new_token);
		}
		else
			i++;
	}
}

int	syntax_error(t_token *tokens)
{
	t_token *curr;;
	int		type;

	curr = tokens;
	while (curr)
	{
		type = curr->type;
		if (type == INPUT || type == OUTPUT || type == APPEND || type == PIPE)
		{
			if (!curr->next || curr->next->type == INPUT || curr->next->type == OUTPUT
				|| curr->next->type == APPEND || curr->next->type == PIPE)
				return (1);
		}
		curr = curr->next;
	}
	return (0);
}

int	process_input(char *input)
{
	t_token *tokens;

	tokens = NULL;
	if (!valid_quotes(input))
		return (0);
	input = add_spaces(input);
	if (!input)
		perror("error");
	ft_split(input, &tokens);
	// Here We'll Start The Execution
	// Tokens Is A linked List Containing all the words from the input
	// to print the tokens remove comment from the next line
	// print_the_shit(tokens);
	if (syntax_error(tokens))
		return (0);
	return (1);
}

int read_input(char *input, char *cwd)
{
	while (1)
	{
		input = readline(cwd);
		if (!input[0])
			continue ;
		if (input[0])
			add_history(input);
		else if (history_length > 0)
				ft_strcpy(input, history_get(history_length)->line);
		if (!process_input(input))
			printf("minishell: syntax error\n");
		free(input);
	}
	return (1);
}

int main(int ac, char **av)
{
	char *cwd;
	char *input;

	if (ac != 1)
		return (printf("minishell: too many arguments\n"), 1);
	(void)av;
	cwd = malloc(BUFFER_SIZE);
	input = NULL;
	if (!cwd)
		perror("error");
	if (getcwd(cwd, BUFFER_SIZE))
		cwd = ft_strjoin(cwd, " » ");
	else
		(perror("error"), free(cwd));
	// handle_signals();
	if (!isatty(STDIN_FILENO))
		exit(1);
	using_history();
	if (!read_input(input, cwd))
		return (1);
	(free(input), free(cwd), printf(" exit\n"), exit(0));
}
