/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouchta <obouchta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 08:42:35 by obouchta          #+#    #+#             */
/*   Updated: 2024/03/08 05:33:13 by obouchta         ###   ########.fr       */
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
		printf("value: (%s)\n", curr->value);
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
					printf("{%s}\n", *curr->args);
					curr->args++;
				}	
		}
		printf("\n");
		curr = curr->next;
	}
}

int	is_whitespace(char c)
{
	int		i;
	char	*set;
	
	i = 0;
	set = " \t\n\v\f\r";
	while (set[i])
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}


int	tokenize_input(char *input, t_token **tokens)
{
	t_token	*new_token;
	int		i;

	i = 0;
	input = ft_strtrim(input);
	while (input[i])
	{
		if (i == 0 || is_whitespace(input[i]))
		{
			while (input[i] && is_whitespace(input[i]))
				i++;
			if (regonize_type(input, i) != EXPRESSION)
				new_token = get_token(input, &i, regonize_type(input, i));
			else
				new_token = get_cmd(input, &i, get_last_type(*tokens));
			if (new_token)
				ft_lstadd_back_1(tokens, new_token);
			else
				return (0);
		}
		else
			i++;
	}
	return (1);
}

int	syntax_error(t_token *tokens)
{
	t_token *curr;;
	int		type;

	curr = tokens;
	if (curr->type == PIPE)
		return (1);
	while (curr)
	{
		type = curr->type;
		if (type == INPUT || type == OUTPUT || type == APPEND)
		{
			if (!curr->next || curr->next->type == INPUT || curr->next->type == OUTPUT
				|| curr->next->type == APPEND || curr->next->type == PIPE)
				return (1);
		}
		if (type == PIPE && (!curr->next || curr->next->type == PIPE))
			return (1);
		curr = curr->next;
	}
	return (0);
}

int	process_input(char *input, t_list **list_env, t_list **list_set)
{
	t_token *tokens;

	tokens = NULL;
	if (!valid_quotes(input))
		return (0);
	input = add_spaces(input);
	printf("input: {%s}\n", input);
	if (!input)
		perror("error");
	tokenize_input(input, &tokens);
	if (!remove_quotes(&tokens))
		perror("error");
	// print_the_shit(tokens);
	if (syntax_error(tokens))
		return (0);
	ft_execution(tokens, list_env, list_set);
	return (1);
}

int read_input(char *cwd, t_list **list_env)
{
	t_list *list_set;
	char 	*input;

	list_set = NULL;
	while (1)
	{
		input = readline(cwd);
		if (!input[0])
			continue ;
		if (!ft_strcmp(input, "exit"))
			exit(0);
		if (input[0])
			add_history(input);
		else if (history_length > 0)
				ft_strcpy(input, history_get(history_length)->line);
		if (!process_input(input, list_env, &list_set))
			printf("minishell: syntax error\n");
		free(input);
	}
	return (1);
}

int main(int ac, char **av, char **envp)
{
	char 		*cwd;
	t_list		*list_env;

	if (ac != 1)
		return (printf("minishell: too many arguments\n"), 1);
	(void)av;
	list_env = env_lst(envp);
	if (!list_env)
		env_init(&list_env);
	cwd = getcwd(NULL, 0);
	if (cwd)
		cwd = ft_strjoin(cwd, " » ");
	else
		(perror("error"));
	if (!isatty(STDIN_FILENO))
		exit(1);
	using_history();
	if (!read_input(cwd, &list_env))
		return (1);
	(free(cwd), printf(" exit\n"), exit(0));
}
